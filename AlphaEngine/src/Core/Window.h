#pragma once

#include <memory>

#include "Core.h"
#include "Render/RenderContext.h"

struct GLFWwindow;

namespace Alpha
{
	class Window
	{
	public:
		Window(int width, int height);

		bool ShouldClose() const;

		void Update();
		void Initialize();

		void SwapBuffers();
	private:
		GLFWwindow* window;
		std::unique_ptr<RenderContext> renderContext;

		int width;
		int height;

		void InitializeWindow();
	};
}

