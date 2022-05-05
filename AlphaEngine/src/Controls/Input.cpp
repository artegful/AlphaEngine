#include "Input.h"

#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"
#include "Events/MouseScrolledEvent.h"

namespace Alpha
{
	bool Input::MouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };
	bool Input::PreviousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };

	bool Input::KeyButtons[GLFW_KEY_LAST + 1]{ false };
	bool Input::PreviousKeyButtons[GLFW_KEY_LAST + 1]{ false };

	glm::vec2 Input::Scroll;
	bool Input::HasScrolled;

	bool Input::IsKeyDown(int keyCode)
	{
		if (keyCode <= GLFW_KEY_LAST)
		{
			return KeyButtons[keyCode];
		}

		return false;
	}

	bool Input::IsKeyPressed(int keyCode)
	{
		if (keyCode <= GLFW_KEY_LAST)
		{
			return KeyButtons[keyCode] && !PreviousKeyButtons[keyCode];
		}

		return false;
	}

	bool Input::IsMouseButtonDown(int keyCode)
	{
		if (keyCode <= GLFW_MOUSE_BUTTON_LAST)
		{
			return MouseButtons[keyCode];
		}

		return false;
	}

	bool Input::IsMouseButtonPressed(int keyCode)
	{
		if (keyCode <= GLFW_MOUSE_BUTTON_LAST)
		{
			return MouseButtons[keyCode] && !PreviousMouseButtons[keyCode];
		}

		return false;
	}

	bool Input::HasScroll()
	{
		return HasScrolled;
	}

	const glm::vec2& Input::GetScroll()
	{
		return Scroll;
	}

	void Input::EndFrame()
	{
		memcpy(PreviousMouseButtons, MouseButtons, sizeof(MouseButtons));
		memcpy(PreviousKeyButtons, KeyButtons, sizeof(KeyButtons));

		Scroll = { 0, 0 };
		HasScrolled = false;
	}

	void Input::OnEvent(Event& event)
	{
		Dispatcher::Dispatch<KeyPressedEvent>(event, OnKeyPressedEvent);
		Dispatcher::Dispatch<KeyReleasedEvent>(event, OnKeyReleasedEvent);
		Dispatcher::Dispatch<MouseButtonPressedEvent>(event, OnMouseButtonPressedEvent);
		Dispatcher::Dispatch<MouseButtonReleasedEvent>(event, OnMouseButtonReleasedEvent);
		Dispatcher::Dispatch<MouseScrolledEvent>(event, OnMouseScrolledEvent);
	}

	bool Input::OnKeyPressedEvent(KeyPressedEvent& event)
	{	
#ifdef AL_DEBUG
		if (event.GetKeyCode() > GLFW_KEY_LAST)
		{
			return false;
		}
#endif
		KeyButtons[event.GetKeyCode()] = true;

		return false;
	}

	bool Input::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
#ifdef AL_DEBUG
		if (event.GetKeyCode() > GLFW_KEY_LAST)
		{
			return false;
		}
#endif
		KeyButtons[event.GetKeyCode()] = false;

		return false;
	}

	bool Input::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		MouseButtons[event.GetMouseButton()] = true;

		return false;
	}

	bool Input::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		MouseButtons[event.GetMouseButton()] = false;

		return false;
	}

	bool Input::OnMouseScrolledEvent(MouseScrolledEvent& event)
	{
		HasScrolled = true;
		Scroll += event.GetScroll();

		return false;
	}
}
