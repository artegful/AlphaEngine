#pragma once

#include <vector>

#include "glm/vec2.hpp"

#include "Sprite.h"

namespace Alpha
{
	class Texture;

	class SpriteSheet
	{
	public:
		SpriteSheet(Texture* texture, glm::ivec2 spriteSize, glm::ivec2 spacing);

		const Sprite* GetSprite(int index);

	private:
		std::vector<Sprite> cutSprites;
	};
}

