#pragma once

#include "glm/vec3.hpp"
#include "Shader.h"

namespace Alpha
{
	struct Light
	{
		glm::vec4 Color = glm::vec4(1.0f);

		glm::vec3 Ambient = glm::vec3(0.3f);
		glm::vec3 Diffuse = glm::vec3(0.7f);
		glm::vec3 Specular = glm::vec3(0.4f);

		float ConstantFalloff = 1.0f;
		float LinearFalloff = 0.09f;
		float QuadraticFalloff = 0.032f;
	};
}