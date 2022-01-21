#pragma once

#include "glm/glm.hpp"

namespace Alpha
{
	class Camera
	{
	public:
		Camera(int width, int height);

		glm::vec2 GetPosition();
		void SetPosition(glm::vec2 position);

		glm::mat4 GetProjectionMatrix();
		glm::mat4 GetViewMatrix();

	private:
		glm::vec2 position;

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;

		void UpdateViewMatrix();
	};
}

