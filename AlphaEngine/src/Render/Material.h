#pragma once

#include "glm/vec3.hpp"
#include "Texture.h"

namespace Alpha
{
	struct Material
	{
		std::shared_ptr<Texture> DiffuseMap;
		std::shared_ptr<Texture> SpecularMap;

		float Shininess = 32.0f;
		glm::vec3 DiffuseColor = glm::vec3(1.0f);
	};
}
