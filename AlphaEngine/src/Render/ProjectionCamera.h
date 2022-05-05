#pragma once

#include "glm/glm.hpp"
#include "Core/Transform.h"

namespace Alpha
{
	class ProjectionCamera
	{
	public:
		virtual ~ProjectionCamera() = default;

		virtual const glm::mat4& GetProjectionMatrix() const = 0;
	};
}

