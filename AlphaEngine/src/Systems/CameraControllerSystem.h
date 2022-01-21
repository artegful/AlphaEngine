#pragma once

#include "ECS/System.h"

namespace Alpha
{
	class CameraControllerSystem : public System
	{
	public:
		CameraControllerSystem(entt::registry& registry) : System(registry)
		{ }

		void Update(float deltaTime) override;
	};
}

