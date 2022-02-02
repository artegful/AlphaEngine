#pragma once

#include "Event.h"

namespace Alpha
{
	struct MouseButtonReleasedEvent : public Event
	{
		MouseButtonReleasedEvent(int keyCode) :
			mouseButton(keyCode)
		{ }

		EVENT_TYPE(EventType::MouseReleased)

		int GetMouseButton() const { return mouseButton; }

	private:
		int mouseButton;
	};
}
