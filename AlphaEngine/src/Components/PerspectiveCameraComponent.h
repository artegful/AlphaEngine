#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "Render/PerspectiveCamera.h"

namespace Alpha
{
	struct PerspectiveCameraComponent
	{
		PerspectiveCamera Camera;

		PerspectiveCameraComponent():
			Camera(16.0f / 9.0f, 90.0f)
		{ }

		PerspectiveCameraComponent(const PerspectiveCamera& camera) :
			Camera(camera)
		{ }
		PerspectiveCameraComponent(const PerspectiveCameraComponent&) = default;

		operator PerspectiveCamera() const
		{
			return Camera;
		}
	};
}