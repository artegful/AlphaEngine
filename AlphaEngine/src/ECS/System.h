#pragma once

#include "entt/entt.hpp"

namespace Alpha
{
	class System
	{
	public:
		System(entt::registry& registry);
		virtual ~System() = default;

		virtual void Start() { }
		virtual void Update(float deltaTime) = 0;

	protected:
		entt::registry& registry;
	};
}


