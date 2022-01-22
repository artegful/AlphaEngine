#pragma once

#include "Event.h"

namespace Alpha
{
	struct MouseButtonPressedEvent : public Event
	{
		MouseButtonPressedEvent(int keyCode) :
			mouseButton(keyCode)
		{ }

		EVENT_TYPE(EventType::MousePressed)

		int GetMouseButton() const { return mouseButton; }

	private:
		int mouseButton;
	};
}
