#pragma once

#include "Event.h"

namespace Alpha
{
	struct KeyPressedEvent : public Event
	{
		KeyPressedEvent(int keyCode) :
			keyCode(keyCode)
		{ }

		EVENT_TYPE(EventType::KeyPressed)

		int GetKeyCode() const { return keyCode; }

	private:
		int keyCode;
	};
}