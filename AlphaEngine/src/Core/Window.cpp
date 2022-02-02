#include "Window.h"

#include <functional>
#include "GLFW/glfw3.h"

#include "Core/Core.h"

#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"

namespace Alpha
{
	std::function<void(Event&)> Window::EventCallback;

	Window::Window(int width, int height, std::function<void(Event&)> eventCallback) :
		width(width), height(height), window(nullptr)
	{
		EventCallback = eventCallback;
	}

	void Window::Initialize()
	{
		InitializeWindow();

		renderContext.reset(RenderContext::Create());
		renderContext->Initialize(window);

		if (EventCallback)
		{
			BindEvents();
		}
		else
		{
			AL_WARNING("Window has no event callback - no input events");
		}
	}

	void Window::Update()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		renderContext->SwapBuffers();
	}

	GLFWwindow* Window::GetNativeWindow()
	{
		return window;
	}

	bool Window::ShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	int Window::GetWidth() const
	{
		return width;
	}

	int Window::GetHeight() const
	{
		return height;
	}

	void Window::InitializeWindow()
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

	void Window::BindEvents()
	{
		glfwSetKeyCallback(window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
			{
				if (key < 0)
				{
					return;
				}

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key);
						EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
			{
				if (button < 0)
				{
					return;
				}

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						EventCallback(event);
						break;
					}
				}
			});
	}
}