#include "Input.h"

namespace Alpha
{
	bool Input::mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };
	bool Input::previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };

	bool Input::keyButtons[GLFW_KEY_LAST + 1]{ false };
	bool Input::previousKeyButtons[GLFW_KEY_LAST + 1]{ false };

	glm::vec2 Input::mousePosition(0);
	glm::vec2 Input::mouseScroll(0);

	bool Input::isDragging{ false };

	void Input::Initialize(GLFWwindow* window)
	{
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetCursorPosCallback(window, CursorPositionCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
		glfwSetScrollCallback(window, ScrollCallback);
	}

	bool Input::IsKeyDown(int keyCode)
	{
		if (keyCode <= GLFW_KEY_LAST)
		{
			return keyButtons[keyCode];
		}

		return false;
	}

	bool Input::IsKeyPressed(int keyCode)
	{
		if (keyCode <= GLFW_KEY_LAST)
		{
			return keyButtons[keyCode] && !previousKeyButtons[keyCode];
		}

		return false;
	}

	bool Input::IsMouseButtonDown(int keyCode)
	{
		if (keyCode <= GLFW_MOUSE_BUTTON_LAST)
		{
			return mouseButtons[keyCode];
		}

		return false;
	}

	bool Input::IsMouseButtonPressed(int keyCode)
	{
		if (keyCode <= GLFW_MOUSE_BUTTON_LAST)
		{
			return mouseButtons[keyCode] && !previousMouseButtons[keyCode];
		}

		return false;
	}

	glm::vec2 Input::GetMousePosition()
	{
		return mousePosition;
	}

	glm::vec2 Input::GetMouseScroll()
	{
		return mouseScroll;
	}

	bool Input::IsDragging()
	{
		return isDragging;
	}


	void Input::EndFrame()
	{
		memcpy(previousMouseButtons, mouseButtons, sizeof(mouseButtons));
		memcpy(previousKeyButtons, keyButtons, sizeof(keyButtons));
	}

	void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key < 0)
		{
			return;
		}

		switch (action)
		{
		case GLFW_PRESS:
			keyButtons[key] = true;
			break;

		case GLFW_RELEASE:
			keyButtons[key] = false;
			break;
		}
	}

	void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		mousePosition.x = (float) xpos;
		mousePosition.y = (float) ypos;

		isDragging = mouseButtons[0];
	}

	void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		switch (action)
		{
		case GLFW_PRESS:
			mouseButtons[button] = true;
			break;

		case GLFW_RELEASE:
			mouseButtons[button] = false;

			if (button == 0)
			{
				isDragging = false;
			}

			break;
		}
	}

	void Input::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		mouseScroll.x = (float) xoffset;
		mouseScroll.y = (float) yoffset;
	}
}
