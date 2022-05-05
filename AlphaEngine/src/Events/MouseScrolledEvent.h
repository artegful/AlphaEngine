#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

namespace Alpha
{
	struct MouseScrolledEvent : public Event
	{
		MouseScrolledEvent(double xScroll, double yScroll) :
			scroll(xScroll, yScroll)
		{ }

		EVENT_TYPE(EventType::Scroll)

		const glm::vec2& GetScroll() const
		{
			return scroll;
		};

	private:
		glm::vec2 scroll;
	};
}