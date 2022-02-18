#pragma once

#include "entt/entt.hpp"
#include "Events/Event.h"

namespace Alpha
{
	class System
	{
	public:
		System(entt::registry& registry);
		virtual ~System() = default;

		virtual void Start() { }
		virtual void Update(float deltaTime) = 0;
		virtual void OnEvent(Event& event) { };

	protected:
		entt::registry& registry;
	};
}


