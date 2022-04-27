#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "Render/ProjectionCamera.h"

namespace Alpha
{
	struct CameraComponent
	{
		ProjectionCamera Camera;

		CameraComponent():
			Camera(16.0f / 9.0f)
		{ }
		CameraComponent(const ProjectionCamera& camera) :
			Camera(camera)
		{ }
		CameraComponent(const CameraComponent&) = default;

		operator ProjectionCamera() const
		{
			return Camera;
		}
	};
}