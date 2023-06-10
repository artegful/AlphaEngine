#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "Sprite.h"
#include "Core/Transform.h"

namespace Alpha
{
	class Sprite;

	struct RenderProperties2D
	{
		Transform Transform;

		std::shared_ptr<Alpha::Sprite> Sprite;
		glm::vec4 Color = glm::vec4(1.0f);

		float Tiling = 1.0f;
	};
}