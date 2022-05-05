#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

namespace Alpha
{
	struct WindowResizedEvent : public Event
	{
		WindowResizedEvent(int width, int height) :
			size(width, height)
		{ }

		EVENT_TYPE(EventType::WindowResized)

		const glm::vec2& GetNewSize() const
		{
			return size;
		};

	private:
		glm::vec2 size;
	};
}