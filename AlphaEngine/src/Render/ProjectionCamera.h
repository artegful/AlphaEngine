#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"

namespace Alpha
{
	class ProjectionCamera
	{
	public:
		ProjectionCamera(glm::vec2 size);
		ProjectionCamera(float width, float height);
		ProjectionCamera(float aspectRatio);

		float GetZoom() const;
		void SetZoom(float zoom);
		glm::vec2 GetSize() const;
		void SetSize(glm::vec2 size);

		void SetAspectRatio(float aspectRatio);

		const glm::mat4& GetProjectionMatrix() const;

	private:
		static constexpr float MIN_ZOOM = 0.001f;

		glm::mat4 projectionMatrix;
		glm::vec2 size;
		float zoom;

		void UpdateProjectionMatrix();
	};
}

