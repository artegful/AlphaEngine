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
		float GetAspectRatio() const;
		void SetAspectRatio(float aspectRatio);

		const glm::mat4& GetProjectionMatrix() const;

	private:
		static constexpr float MIN_ZOOM = 0.001f;

		glm::mat4 projectionMatrix;
		float aspectRatio;
		float zoom;

		void UpdateProjectionMatrix();
	};
}

