#pragma once

#include "glfw/glfw3.h"
#include "glm/vec2.hpp"
#include <Events/MouseMovedEvent.h>

namespace Alpha
{
	struct Event;
	struct KeyPressedEvent;
	struct KeyReleasedEvent;
	struct MouseButtonPressedEvent;
	struct MouseButtonReleasedEvent;
	struct MouseScrolledEvent;

	class Input
	{
	public:
		static bool IsKeyDown(int keyCode);
		static bool IsKeyPressed(int keyCode);

		static bool IsMouseButtonDown(int keyCode);
		static bool IsMouseButtonPressed(int keyCode);

		static glm::vec2 GetMousePos();
		static glm::vec2 GetMouseDelta();
		static void SetMousePos(glm::vec2 position);

		static bool HasScroll();
		static const glm::vec2& GetScroll();

		static void OnEvent(Event& event);
		static void EndFrame();

	private:
		static bool MouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];
		static bool PreviousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1];

		static bool KeyButtons[GLFW_KEY_LAST + 1];
		static bool PreviousKeyButtons[GLFW_KEY_LAST + 1];

		static glm::vec2 Scroll;
		static bool HasScrolled;

		static glm::vec2 MousePosition;
		static glm::vec2 PreviousMousePosition;

		static bool OnMouseMovedEvent(MouseMovedEvent& event);
		static bool OnKeyPressedEvent(KeyPressedEvent& event);
		static bool OnKeyReleasedEvent(KeyReleasedEvent& event);
		static bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
		static bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
		static bool OnMouseScrolledEvent(MouseScrolledEvent& event);
	};
}
