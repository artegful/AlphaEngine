#pragma once

#include "glm/vec2.hpp"

class b2Body;

namespace Alpha
{
	struct Rigidbody2DComponent
	{
		enum class BodyType
		{
			Static,
			Dynamic,
			Kinematic
		};

		Rigidbody2DComponent() = default;
		Rigidbody2DComponent(const Rigidbody2DComponent&) = default;

		b2Body* Body;

		BodyType Type = BodyType::Dynamic;
		bool IsFixedRotation = false;

		void AddForce(glm::vec2 direction, float force = 1.0f);
	};
}