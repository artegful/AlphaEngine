#pragma once

#include <vector>

#include "ECS/System.h"
#include "Render/SpriteBatch.h"

namespace Alpha
{
	class SpriteRenderSystem : public System
	{
	public:
		SpriteRenderSystem(entt::registry& registry);

		void Start() override;
		void Update(float deltaTime) override;

	private:
		std::vector<SpriteBatch> spriteBatches;

		void AddToNearestBatch(const TransformComponent& transform, const SpriteComponent& sprite);
	};
}


