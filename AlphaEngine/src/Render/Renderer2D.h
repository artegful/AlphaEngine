#pragma once

#include <memory>
#include <array>
#include "glm/glm.hpp"
#include "Camera.h"
#include "SpriteProperties.h"

namespace Alpha
{
	class VertexArray;
	class VertexBuffer;
	class Shader;
	class Texture;

	class Renderer2D
	{
	public:
		static void Initialize();
		static void Shutdown();

		static void BeginScene(const Camera& camera);
		static void DrawQuad(const SpriteProperties properties);
		static void EndScene();

	private:
		struct Vertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 Uv;
			float TextureIndex;
			float Tiling;
		};

		struct RenderData
		{
			static constexpr size_t MAX_SPRITES = 10000;
			static constexpr size_t MAX_VERTICES = MAX_SPRITES * 4;
			static constexpr size_t MAX_INDICES = MAX_SPRITES * 6;
			static constexpr size_t MAX_TEXTURES = 32;

			std::shared_ptr<VertexArray> VertexArray;
			std::shared_ptr<VertexBuffer> VertexBuffer;

			std::shared_ptr<Shader> Shader;

			Vertex* Vertices;
			Vertex* NextEmptyVertex;
			size_t SpritesStored;

			std::array<std::shared_ptr<Texture>, MAX_TEXTURES> Textures;
			size_t NextTextureIndex;
		};

		static RenderData Data;

		static void Flush();
		static int FindOrAddTexture(const std::shared_ptr<Texture> texture);
	};
}

