#include "SpriteBatch.h"

#include <stdexcept>

#include "Texture.h"
#include "Sprite.h"

#include "Resources/ResourceAllocator.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"

namespace Alpha
{
	SpriteBatch::SpriteBatch() : 
		shader{ Resources::ResourceAllocator<ShaderProgram>::Get().Add("assets/shaders/default") },
		amountStored(0),
		textures{}
	{
		GenerateIndexBuffer();

		glGenVertexArrays(1, &vaoId);
		glBindVertexArray(vaoId);

		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuffer), NULL, GL_DYNAMIC_DRAW);

		glGenBuffers(1, &eboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexBuffer), indexBuffer, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), 0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*) sizeof(vertexBuffer[0].Position));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*) (sizeof(vertexBuffer[0].Position) + sizeof(vertexBuffer[0].Color)));
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), 
			(void*)(sizeof(vertexBuffer[0].Position) + sizeof(vertexBuffer[0].Color) + sizeof(vertexBuffer[0].Uv)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	bool SpriteBatch::HasSpace() const
	{
		return amountStored < MAX_SPRITES;
	}

	bool SpriteBatch::HasTexture(const Texture* texture) const
	{
		return std::find(textures.begin(), textures.end(), texture) != textures.end();
	}

	bool SpriteBatch::HasTextureSpace() const
	{
		return textures.size() < MAX_TEXTURES;
	}

	void SpriteBatch::AddSprite(const SpriteComponent& sprite, const TransformComponent& transform)
	{
		if (amountStored >= MAX_SPRITES)
		{
			throw std::invalid_argument("Batch is already full");
		}

		int textureId = -1;

		if (sprite.Sprite->GetTexture())
		{
			auto findResult = std::find(textures.begin(), textures.end(), sprite.Sprite->GetTexture());

			if (findResult == textures.end())
			{
				textureId = textures.size();

				textures.push_back(sprite.Sprite->GetTexture());
			}
			else
			{
				textureId = std::distance(textures.begin(), findResult);
			}
		}

		glm::mat4 transformMatrix = transform.GetTransform();

		const glm::vec2* uvCoords = sprite.Sprite->GetUvCoords();

		QuadVertex verticesInQuad[VERTICES_IN_SPRITE] 
		{ 
			{ transformMatrix * glm::vec4{ -0.5f, -0.5f, 0.0f, 1.0f }, sprite.Color, uvCoords[0], textureId },
			{ transformMatrix * glm::vec4{  0.5f, -0.5f, 0.0f, 1.0f }, sprite.Color, uvCoords[1], textureId },
			{ transformMatrix * glm::vec4{  0.5f,  0.5f, 0.0f, 1.0f }, sprite.Color, uvCoords[2], textureId },
			{ transformMatrix * glm::vec4{ -0.5f,  0.5f, 0.0f, 1.0f }, sprite.Color, uvCoords[3], textureId }
		};


		memcpy(vertexBuffer + amountStored * VERTICES_IN_SPRITE, verticesInQuad, sizeof(verticesInQuad));
		amountStored++;
	}

	void SpriteBatch::Draw(CameraComponent camera, TransformComponent cameraTransform)
	{
		int textureIds[] { 0, 1, 2, 3, 4, 5, 6, 7 };

		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexBuffer), vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		shader->Use();
		shader->SetUniformMatrix4f("projection", camera.GetProjection());
		shader->SetUniformMatrix4f("view", cameraTransform.GetInverseTransform());
		shader->SetUniformIntPointer("textures", textureIds, MAX_TEXTURES);

		glBindVertexArray(vaoId);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);

		int i = 0;
		for (auto it = textures.begin(); it != textures.end(); it++, i++)
		{
			(*it)->UseInSlot(i);
		}

		glDrawElements(GL_TRIANGLES, amountStored * INDICES_IN_SPRITE, GL_UNSIGNED_INT, 0);

		for (auto texture : textures)
		{
			texture->Detach();
		}

		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(0);
		glBindVertexArray(0);

		shader->Detach();
	}

	void SpriteBatch::GenerateIndexBuffer()
	{
		for (auto i = 0; i < MAX_SPRITES; i++)
		{
			//0 1 2 0 2 3

			int indexOffset = INDICES_IN_SPRITE * i;
			int vertexOffset = VERTICES_IN_SPRITE * i;

			indexBuffer[indexOffset    ] = vertexOffset;
			indexBuffer[indexOffset + 1] = vertexOffset + 1;
			indexBuffer[indexOffset + 2] = vertexOffset + 2;

			indexBuffer[indexOffset + 3] = vertexOffset;
			indexBuffer[indexOffset + 4] = vertexOffset + 2;
			indexBuffer[indexOffset + 5] = vertexOffset + 3;
		}
	}
}

