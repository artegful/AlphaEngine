#pragma once

#include "glm/vec4.hpp"
#include "API.h"

namespace Alpha
{
	class RendererAPI
	{
	public:
		virtual ~RendererAPI() = default;

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed() = 0;

		static API GetAPI();
		static RendererAPI* Create();

	private:
		static API Api;

		friend class RenderCommand;
	};
}
