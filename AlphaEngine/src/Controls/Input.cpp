#include "Input.h"

#include "Events/KeyPressedEvent.h"
#include "Events/KeyReleasedEvent.h"
#include "Events/MouseButtonPressedEvent.h"
#include "Events/MouseButtonReleasedEvent.h"

namespace Alpha
{
	bool Input::mouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };
	bool Input::previousMouseButtons[GLFW_MOUSE_BUTTON_LAST + 1]{ false };

	bool Input::keyButtons[GLFW_KEY_LAST + 1]{ false };
	bool Input::previousKeyButtons[GLFW_KEY_LAST + 1]{ false };

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

	void Input::EndFrame()
	{
		memcpy(previousMouseButtons, mouseButtons, sizeof(mouseButtons));
		memcpy(previousKeyButtons, keyButtons, sizeof(keyButtons));
	}

	void Input::OnEvent(Event& event)
	{
		Dispatcher::Dispatch<KeyPressedEvent>(event, OnKeyPressedEvent);
		Dispatcher::Dispatch<KeyReleasedEvent>(event, OnKeyReleasedEvent);
		Dispatcher::Dispatch<MouseButtonPressedEvent>(event, OnMouseButtonPressedEvent);
		Dispatcher::Dispatch<MouseButtonReleasedEvent>(event, OnMouseButtonReleasedEvent);
	}

	bool Input::OnKeyPressedEvent(KeyPressedEvent& event)
	{	
		keyButtons[event.GetKeyCode()] = true;

		return false;
	}

	bool Input::OnKeyReleasedEvent(KeyReleasedEvent& event)
	{
		keyButtons[event.GetKeyCode()] = false;

		return false;
	}

	bool Input::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
	{
		mouseButtons[event.GetMouseButton()] = true;

		return false;
	}

	bool Input::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
	{
		mouseButtons[event.GetMouseButton()] = false;

		return false;
	}
}
