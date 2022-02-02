#pragma once

#include "glm/glm.hpp"
#include "Texture.h"

namespace Alpha
{
	struct SpriteProperties
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec2 Size = glm::vec2(1.0f);
		float RotationAngle = 0.0f;

		std::shared_ptr<Texture> Texture = nullptr;
		glm::vec4 Color = glm::vec4(1.0f);

		float Tiling = 1.0f;
	};
}