#pragma once

#include "glm/gtc/matrix_transform.hpp"

namespace Alpha
{
	struct CameraComponent
	{
		static constexpr float VIEWPORT_SCALE = 2.0f;

		CameraComponent(float aspectRatio)
		{
			projection = glm::ortho(-VIEWPORT_SCALE * aspectRatio, VIEWPORT_SCALE * aspectRatio, -VIEWPORT_SCALE, VIEWPORT_SCALE);
		}
		CameraComponent(glm::mat4 projection) :
			projection(projection)
		{ }
		CameraComponent(const CameraComponent&) = default;

		glm::mat4 GetProjection() const { return projection; };

	private:
		glm::mat4 projection;
	};
}