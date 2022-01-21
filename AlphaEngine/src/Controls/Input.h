#pragma once

#include "glfw/glfw3.h"
#include "glm/vec2.hpp"

namespace Alpha
{
	class Input
	{
	public:
		static bool IsKeyDown(int keyCode);
		static bool IsKeyPressed(int keyCode);

		static bool IsMouseButtonDown(int keyCode);
		static bool IsMouseButtonPressed(int keyCode);

		static glm::vec2 GetMousePosition();
		static glm::vec2 GetMouseScroll();

		static bool IsDragging();

		static void Initialize(GLFWwindow* window);
		static void EndFrame();

	private:
		static bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
		static bool previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

		static bool keyButtons[GLFW_KEY_LAST + 1];
		static bool previousKeyButtons[GLFW_KEY_LAST + 1];

		static glm::vec2 mousePosition;
		static glm::vec2 mouseScroll;

		static bool isDragging;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
		static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	};
}
