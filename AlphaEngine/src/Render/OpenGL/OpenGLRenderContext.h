#pragma once

#include "Render/RenderContext.h"

namespace Alpha
{
	class OpenGLRenderContext : public RenderContext
	{
	public:
		void Initialize(GLFWwindow* window) override;
		void SwapBuffers() override;

	private:
		GLFWwindow* window;
	};
}

