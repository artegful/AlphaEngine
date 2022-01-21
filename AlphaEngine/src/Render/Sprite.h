#pragma once

#include "glm/vec2.hpp"

#include "Texture.h"

namespace Alpha
{
	class Sprite
	{
	public:
		Sprite(Texture* texture);
		Sprite(Texture* texture, glm::vec2 uvCoords[4]);

		const glm::vec2* GetUvCoords() const;
		const Texture* GetTexture() const;

	private:
		Texture* texture;
		glm::vec2 uvCoords[4];
	};
}
