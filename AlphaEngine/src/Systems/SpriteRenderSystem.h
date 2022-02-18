#pragma once

#include <vector>
#include "ECS/System.h"

namespace Alpha
{
	struct WindowResizedEvent;

	class SpriteRenderSystem : public System
	{
	public:
		SpriteRenderSystem(entt::registry& registry);

		void Update(float deltaTime) override;
	};
}


