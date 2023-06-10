#include "GlfwWindow.h"

#include <functional>
#include "GLFW/glfw3.h"

#include "Core/Core.h"

#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"
#include "Events/MouseScrolledEvent.h"
#include "Events/MouseMovedEvent.h"

namespace Alpha
{
	GlfwWindow::GlfwWindow(int width, int height) :
		width(width), height(height), window(nullptr)
	{ }

	void GlfwWindow::Initialize()
	{
		InitializeWindow();

		MakeContextCurrent();
		renderContext.reset(RenderContext::Create());
		renderContext->Initialize(window);
	}

	void GlfwWindow::Update()
	{
		glfwPollEvents();
	}

	void GlfwWindow::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}

	void GlfwWindow::SetEventCallback(std::function<void(Event&)> callback)
	{
		eventCallback = callback;

		BindEvents();
	}

	GLFWwindow* GlfwWindow::GetNativeWindow()
	{
		return window;
	}

	bool GlfwWindow::ShouldClose() const
	{
		return glfwWindowShouldClose(window);
	}

	int GlfwWindow::GetWidth() const
	{
		return width;
	}

	int GlfwWindow::GetHeight() const
	{
		return height;
	}

	void GlfwWindow::InitializeWindow()
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

	void GlfwWindow::MakeContextCurrent()
	{
		glfwMakeContextCurrent(window);
	}

	void GlfwWindow::BindEvents()
	{
		glfwSetWindowUserPointer(window, this);

		glfwSetKeyCallback(window, [](GLFWwindow* glfwWindow, int key, int scancode, int action, int mods)
			{
				if (key < 0)
				{
					return;
				}

				GlfwWindow* window = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key);
					window->eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					window->eventCallback(event);
					break;
				}
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* glfwWindow, int button, int action, int mods)
			{
				if (button < 0)
				{
					return;
				}

				GlfwWindow* window = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					window->eventCallback(event);

					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					window->eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(window, [](GLFWwindow* glfwWindow, double xoffset, double yoffset)
			{
				GlfwWindow* window = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

				MouseScrolledEvent event(xoffset, yoffset);
				window->eventCallback(event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* glfwWindow, double xpos, double ypos)
			{
				GlfwWindow* window = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(glfwWindow));

				MouseMovedEvent event({ xpos, ypos });
				window->eventCallback(event);
			});
	}
}