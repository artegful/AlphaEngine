#pragma once

#include "glm/vec4.hpp"
#include "API.h"

namespace Alpha
{
	class VertexArray;
	class Shader;

	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void Initialize() = 0;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const VertexArray& vertexArray) = 0;
		virtual void DrawIndexed(const VertexArray& vertexArray, size_t amount) = 0;

		static API GetAPI();
		static RendererAPI* Create();

	private:
		static API Api;

		friend class RenderCommand;
	};
}
