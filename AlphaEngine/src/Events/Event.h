#pragma once

#include <functional>
#include <utility>

namespace Alpha
{
	enum class EventType
	{
		KeyPressed, KeyReleased, MousePressed, MouseReleased, Scroll
	};

	#define EVENT_TYPE(type) static EventType Type() { return type; }\
							 EventType GetType() const override { return type; }

	#define EVENT_BIND(callback) [this](auto&&... args) -> decltype(auto) { return this->callback(std::forward<decltype(args)>(args)...); }

	struct Event
	{
		bool IsDispatched = false;
		virtual EventType GetType() const = 0;
	};

	class Dispatcher
	{
	public:
		template<typename T>
		static void Dispatch(Event& message, std::function<bool(T&)> callback)
		{
			if (message.GetType() == T::Type())
			{
				message.IsDispatched |= callback(static_cast<T&>(message));
			}
		}
	};

}