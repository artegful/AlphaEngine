#pragma once

#include <memory>
#include "glm/vec2.hpp"
#include "Render/RendererAPI.h"

namespace Alpha
{
	class VertexArray;
	class Shader;

	class RenderCommand
	{
	public:
		static void Initialize();

		static void SetAPI(API api);

		static void DrawIndexed(const VertexArray& vertexArray);
		static void DrawIndexed(const VertexArray& vertexArray, size_t amount);

		static void SetClearColor(const glm::vec4& color);
		static void Clear();

	private:
		static std::unique_ptr<RendererAPI> RendererApi;
	};
}