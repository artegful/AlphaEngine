#pragma once

#include "glm/vec3.hpp"
#include <memory>

namespace Alpha
{
	class Sprite;

	struct SpriteComponent
	{
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };
		
		std::shared_ptr<Alpha::Sprite> Sprite;
	};
}