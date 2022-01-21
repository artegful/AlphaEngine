#include "Window.h"

#include "GLFW/glfw3.h"
#include "Core/Core.h"
#include "Controls/Input.h"

namespace Alpha
{
	Alpha::Window::Window(int width, int height) :
		width(width), height(height), window(nullptr)
	{ }

	void Window::Initialize()
	{
		InitializeWindow();

		renderContext.reset(RenderContext::Create());
		renderContext->Initialize(window);

		//TODO maybe move up a layer?
		Input::Initialize(window);
	}

	void Alpha::Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		renderContext->SwapBuffers();
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	void Alpha::Window::InitializeWindow()
	{
		if (!glfwInit())
		{
			glfwTerminate();

			AL_ENGINE_ASSERT(false, "GLFW failed to initialize");
		}

		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

		window = glfwCreateWindow(width, height, "Application", NULL, NULL);

		if (!window)
		{
			glfwDestroyWindow(window);
			glfwTerminate();

			AL_ENGINE_ASSERT(false, "GLFW failed to create a window");
		}

		glfwShowWindow(window);
	}
}