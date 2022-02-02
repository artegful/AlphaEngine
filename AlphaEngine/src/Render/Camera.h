#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"

namespace Alpha
{
	class Camera
	{
	public:
		Camera(glm::vec2 size);
		Camera(float width, float height);

		Transform& GetTransform();
		glm::mat4 GetProjectionMatrix() const;
		glm::mat4 GetViewMatrix() const;
		glm::mat4 GetViewProjectionMatrix() const;

	private:
		Transform transform;

		glm::mat4 projectionMatrix;
	};
}

