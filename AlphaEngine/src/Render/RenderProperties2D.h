#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "Sprite.h"

namespace Alpha
{
	class Sprite;

	struct RenderProperties2D
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 Size = glm::vec2(1.0f);
		float RotationAngle = 0.0f;

		std::shared_ptr<Alpha::Sprite> Sprite;
		glm::vec4 Color = glm::vec4(1.0f);

		float Tiling = 1.0f;
	};
}