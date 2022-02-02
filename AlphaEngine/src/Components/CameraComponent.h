#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "Render/Camera.h"

namespace Alpha
{
	struct CameraComponent
	{
		Camera Camera;

		CameraComponent(const Alpha::Camera& camera) :
			Camera(camera)
		{ }
		CameraComponent(const CameraComponent&) = default;
	};
}