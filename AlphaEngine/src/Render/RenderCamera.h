#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"
#include "ProjectionCamera.h"

namespace Alpha
{
	class RenderCamera
	{
	public:
		RenderCamera(const ProjectionCamera& camera, const Transform& transform);

		glm::mat4 GetViewProjectionMatrix() const;
		const Transform& GetTransform() const;

	private:
		const ProjectionCamera& camera;
		const Transform& transform;
	};
}