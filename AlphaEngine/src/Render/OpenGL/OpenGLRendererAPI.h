#pragma once

#include "Render/RendererAPI.h"

namespace Alpha
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color);
		void Clear();

		void DrawIndexed();
	};
}