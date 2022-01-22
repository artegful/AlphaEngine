#pragma once

#include "glfw/glfw3.h"
#include "glm/vec2.hpp"

namespace Alpha
{
	struct Event;
	struct KeyPressedEvent;
	struct KeyReleasedEvent;
	struct MouseButtonPressedEvent;
	struct MouseButtonReleasedEvent;

	class Input
	{
	public:
		static bool IsKeyDown(int keyCode);
		static bool IsKeyPressed(int keyCode);

		static bool IsMouseButtonDown(int keyCode);
		static bool IsMouseButtonPressed(int keyCode);

		static void OnEvent(Event& event);
		static void EndFrame();

	private:
		static bool mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
		static bool previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

		static bool keyButtons[GLFW_KEY_LAST + 1];
		static bool previousKeyButtons[GLFW_KEY_LAST + 1];

		static bool OnKeyPressedEvent(KeyPressedEvent& event);
		static bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		static bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		static bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
	};
}
