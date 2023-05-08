#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

namespace Alpha
{
	struct MouseMovedEvent : public Event
	{
		MouseMovedEvent(glm::vec2 position) :
			position(position)
		{ }

		EVENT_TYPE(EventType::MouseMoved)

		glm::vec2 GetPos() const { return position; }

	private:
		glm::vec2 position;
	};
}