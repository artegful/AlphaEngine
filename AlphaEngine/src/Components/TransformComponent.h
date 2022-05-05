#pragma once

#include "rttr/type.h"
#include "rttr/rttr_enable.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/quaternion.hpp"

#include "Core/Transform.h"

namespace Alpha
{
	struct TransformComponent
	{
		Transform Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const Alpha::Transform& transform) : Transform(transform)
		{ }

		operator Alpha::Transform() const
		{
			return Transform;
		}
	};
}