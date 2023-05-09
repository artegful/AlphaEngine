#pragma once

#include "glm/vec3.hpp"

namespace Alpha
{
	struct Material
	{
		glm::vec3 Ambient = glm::vec3(0.3f);
		glm::vec3 Diffuse = glm::vec3(0.8f);
		glm::vec3 Specular = glm::vec3(0.6f);
		float Shininess = 32.0f;
	};
}
