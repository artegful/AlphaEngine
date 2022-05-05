#pragma once

#include "glm/vec2.hpp"

namespace Alpha
{
	struct Box2DColliderComponent
	{
		Box2DColliderComponent() = default;
		Box2DColliderComponent(const Box2DColliderComponent&) = default;

		glm::vec2 Offset { 0.0f, 0.0f };
		glm::vec2 Size { 1.0f, 1.0f };
		float Density = 1.0f;
		float Friction = 0.5f;
		float Restitution = 0.0f;
		float RestitutionThreshold = 0.5f;

		void* RuntimeFixture;
	};
}