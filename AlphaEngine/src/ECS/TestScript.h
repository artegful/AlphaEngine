#pragma once

#include "Script.h"

namespace Alpha
{
	class TestScript : public Script
	{
	public:
		TestScript(const Entity& entity, entt::registry& registry);

		void Update(float deltaTime) override;
		void Start() override;

	private:
		float forceMeter = 0.0f;
		float previousForceMultiplier = 0.0f;
		bool isInJump = false;
		float framesWithoutJump = 0;
		constexpr static float MaxJumpForce = 15.0f;

		void UpdateJumping(float deltaTime);
		void UpdateMovement(float deltaTime);
		void UpdateCameraFollower();
		void Jump(float force);
	};
}