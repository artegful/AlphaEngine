#pragma once

#include "glm/gtc/matrix_transform.hpp"
#include "Render/OrthoCamera.h"

namespace Alpha
{
	struct OrthoCameraComponent
	{
		OrthoCamera Camera;

		OrthoCameraComponent():
			Camera(16.0f / 9.0f)
		{ }
		OrthoCameraComponent(const OrthoCamera& camera) :
			Camera(camera)
		{ }
		OrthoCameraComponent(const OrthoCameraComponent&) = default;

		operator OrthoCamera() const
		{
			return Camera;
		}
	};
}