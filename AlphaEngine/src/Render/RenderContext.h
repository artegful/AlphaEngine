#pragma once

struct GLFWwindow;

namespace Alpha
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;

		virtual void Initialize(GLFWwindow* window) = 0;
		virtual void SwapBuffers() = 0;

		static RenderContext* Create();
	};
}

