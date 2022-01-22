#pragma once

#include "Event.h"

namespace Alpha
{
	struct KeyReleasedEvent : public Event
	{
		KeyReleasedEvent(int keyCode) :
			keyCode(keyCode)
		{ }

		EVENT_TYPE(EventType::KeyReleased)

		int GetKeyCode() const { return keyCode; }

	private:
		int keyCode;
	};
}