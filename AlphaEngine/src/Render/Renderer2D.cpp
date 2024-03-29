#include "Renderer2D.h"

#include <array>

#include "glm/gtc/matrix_transform.hpp"
#include "RenderCommand.h"
#include "Resources/ResourceAllocator.hpp"

#include "RenderCamera.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Sprite.h"

namespace Alpha
{
	GLuint vertexArrayId;
	std::shared_ptr<IndexBuffer> indexBuffer;
	std::shared_ptr<VertexBuffer> buffer;

	GLuint vbo;
	GLuint ebo;

	Renderer2D::RenderData Renderer2D::Data;
	Renderer2D::StatsData Renderer2D::Stats;

	glm::vec2 Renderer2D::RenderData::DefaultUvs[4]
	{
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f }
	};

	void Renderer2D::Initialize()
	{
		Data.Vertices = new Vertex[RenderData::MAX_VERTICES];

		Data.Shader = ResourceAllocator<Shader>::Get("assets/shaders/textureOrColor.glsl");

		uint32_t white = 0xffffffff;
		std::shared_ptr<Texture> blankTexture = Texture::Create(1, 1);
		blankTexture->SetData(&white, 1, 4);
		Data.Textures[0] = blankTexture;
		Data.NextTextureIndex = 1;

		Data.VertexArray = VertexArray::Create();
		Data.VertexArray->Bind();

		Data.VertexBuffer = VertexBuffer::Create(RenderData::MAX_VERTICES * sizeof(Vertex));
		std::shared_ptr<BufferLayout> layout(new BufferLayout
			{ 
				{ ElementType::Float3, "vPosition" },
				{ ElementType::Float4, "vColor" },
				{ ElementType::Float2, "vUv" },
				{ ElementType::Float, "vTextureIndex" },
				{ ElementType::Float, "vTiling" }
			});
		Data.VertexBuffer->SetLayout(layout);

		uint32_t* indices = new uint32_t[RenderData::MAX_INDICES];
		uint32_t offset = 0;
		for (size_t i = 0; i < RenderData::MAX_INDICES; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 0;
			indices[i + 4] = offset + 2;
			indices[i + 5] = offset + 3;

			offset += 4;
		}

		std::shared_ptr<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, RenderData::MAX_INDICES);
		delete[] indices;

		Data.VertexArray->AddVertexBuffer(Data.VertexBuffer);
		Data.VertexArray->SetIndexBuffer(indexBuffer);

		int textureSamplers[RenderData::MAX_TEXTURES];

		for (auto i = 0; i < RenderData::MAX_TEXTURES; i++)
		{
			textureSamplers[i] = i;
		}

		Data.Shader->Bind();
		Data.Shader->SetIntArray("uTextures", textureSamplers, RenderData::MAX_TEXTURES);
	}

	void Renderer2D::Shutdown()
	{
	}

	void Renderer2D::BeginScene(const RenderCamera& camera)
	{
		Data.Shader->Bind();
		Data.Shader->SetMat4("uViewProjectionMatrix", camera.GetViewProjectionMatrix());

		ClearBatch();
	}

	void Renderer2D::DrawQuad(const RenderProperties2D& properties)
	{
		if (Data.SpritesStored >= RenderData::MAX_SPRITES)
		{
			Flush();
		}

		glm::vec4 positions[]
		{
			{ -0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f, -0.5f, 0.0f, 1.0f },
			{  0.5f,  0.5f, 0.0f, 1.0f },
			{ -0.5f,  0.5f, 0.0f, 1.0f }
		};

		glm::mat4 transformation = properties.Transform.GetTransformMatrix();

		float textureId = 0.0f;
		const glm::vec2 *uvs = RenderData::DefaultUvs;

		if (properties.Sprite && properties.Sprite->HasTexture())
		{
			uvs = properties.Sprite->GetUvs();
			textureId = (float)FindOrAddTexture(properties.Sprite->GetTexture());
		}

		for (auto i = 0; i < 4; i++)
		{
			Data.NextEmptyVertex->Position = transformation * positions[i];
			Data.NextEmptyVertex->Color = properties.Color;
			Data.NextEmptyVertex->Uv = uvs[i];
			Data.NextEmptyVertex->TextureIndex = textureId;
			Data.NextEmptyVertex->Tiling = properties.Tiling;
			Data.NextEmptyVertex++;
		}

		Data.SpritesStored++;
		Stats.Quads++;
	}

	void Renderer2D::EndScene()
	{
		Flush();
	}

	const Renderer2D::StatsData& Renderer2D::GetStats()
	{
		return Stats;
	}

	void Renderer2D::ResetStats()
	{
		Stats.Reset();
	}

	void Renderer2D::Flush()
	{
		UploadData();
		Data.VertexArray->Bind();

		for (size_t i = 0; i < Data.NextTextureIndex; i++)
		{
			Data.Textures[i]->Bind(i);
		}

		RenderCommand::DrawIndexed(*Data.VertexArray, 6 * Data.SpritesStored);
		Stats.DrawCalls++;

		ClearBatch();
	}

	void Renderer2D::UploadData()
	{
		Data.VertexBuffer->SetData(Data.Vertices, (uint8_t*)Data.NextEmptyVertex - (uint8_t*)Data.Vertices);
	}

	void Renderer2D::ClearBatch()
	{
		Data.NextEmptyVertex = Data.Vertices;
		Data.SpritesStored = 0;

		for (size_t i = 1; i < Data.NextTextureIndex; i++)
		{
			Data.Textures[i].reset();
		}

		Data.NextTextureIndex = 1;
	}

	int Renderer2D::FindOrAddTexture(const std::shared_ptr<Texture> texture)
	{
		for (size_t i = 0; i < Data.NextTextureIndex; i++)
		{
			if (*Data.Textures[i].get() == *texture.get())
			{
				return i;
			}
		}

		if (Data.NextTextureIndex >= RenderData::MAX_TEXTURES)
		{
			Flush();
		}

		Data.Textures[Data.NextTextureIndex] = texture;
		Data.NextTextureIndex++;
		return Data.NextTextureIndex - 1;
	}

	void Renderer2D::StatsData::Reset()
	{
		memset(this, 0, sizeof(StatsData));
	}
}
