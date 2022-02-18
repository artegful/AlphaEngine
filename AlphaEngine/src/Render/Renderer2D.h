#pragma once

#include <memory>
#include <array>
#include "glm/glm.hpp"
#include "RenderProperties2D.h"

namespace Alpha
{
	class RenderCamera;
	class VertexArray;
	class VertexBuffer;
	class Shader;
	class Texture;

	class Renderer2D
	{
	public:
		struct StatsData
		{
			uint32_t Quads = 0;
			uint32_t DrawCalls = 0;

			void Reset();
		};

		static void Initialize();
		static void Shutdown();

		static void BeginScene(const RenderCamera& camera);
		static void DrawQuad(const RenderProperties2D& properties);
		static void EndScene();

		static const StatsData& GetStats();
		static void ResetStats();

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
			static constexpr size_t MAX_SPRITES = 5000;
			static constexpr size_t MAX_VERTICES = MAX_SPRITES * 4;
			static constexpr size_t MAX_INDICES = MAX_SPRITES * 6;
			static constexpr size_t MAX_TEXTURES = 32;
			static glm::vec2 DefaultUvs[4];

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
		static StatsData Stats;

		static void Flush();
		static void UploadData();
		static void ClearBatch();
		static int FindOrAddTexture(const std::shared_ptr<Texture> texture);
	};
}

