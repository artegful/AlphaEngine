#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"

#include "ProjectionCamera.h"

namespace Alpha
{
	class OrthoCamera : public ProjectionCamera
	{
	public:
		OrthoCamera(glm::vec2 size);
		OrthoCamera(float width, float height);
		OrthoCamera(float aspectRatio);

		float GetZoom() const;
		void SetZoom(float zoom);
		glm::vec2 GetSize() const;
		void SetSize(glm::vec2 size);

		void SetAspectRatio(float aspectRatio);

		const glm::mat4& GetProjectionMatrix() const override;

	private:
		static constexpr float MIN_ZOOM = 0.001f;

		glm::mat4 projectionMatrix;
		glm::vec2 size;
		float zoom;

		void UpdateProjectionMatrix();
	};
}

