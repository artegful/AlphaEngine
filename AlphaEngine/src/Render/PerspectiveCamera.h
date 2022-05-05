#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"

#include "ProjectionCamera.h"

namespace Alpha
{
	class PerspectiveCamera : public ProjectionCamera
	{
	public:
		PerspectiveCamera(float width, float height, float fov);
		PerspectiveCamera(float aspectRatio, float fov);

		float GetZoom() const;
		void SetZoom(float zoom);
		float GetAspectRatio() const;
		void SetAspectRatio(float aspectRatio);
		glm::vec2 GetNearFarPlane() const;
		void SetNearFarPlane(glm::vec2 nearFarPlane);

		const glm::mat4& GetProjectionMatrix() const override;

	private:
		static constexpr float MIN_ZOOM = 0.1f;
		static constexpr float MAX_ZOOM = 1.5f;


		glm::mat4 projectionMatrix;
		float aspectRatio;
		float fov;
		glm::vec2 nearFarPlane;
		float zoom;

		void UpdateProjectionMatrix();
	};
}

