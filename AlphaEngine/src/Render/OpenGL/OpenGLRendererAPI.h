#pragma once

#include "Render/RendererAPI.h"

namespace Alpha
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Initialize() override;

		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const VertexArray& vertexArray) override;
		void DrawIndexed(const VertexArray& vertexArray, size_t amount) override;
	};
}