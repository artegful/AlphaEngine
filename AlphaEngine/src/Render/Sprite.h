#pragma once

#include <memory>
#include "glm/vec2.hpp"

#include "Texture.h"

namespace Alpha
{
	class Sprite
	{
	public:
		Sprite(std::shared_ptr<Texture>& texture);
		Sprite(std::shared_ptr<Texture>& texture, glm::vec2 uvCoords[4]);

		const glm::vec2* GetUvCoords() const;

		std::shared_ptr<Texture> GetTexture() const;

	private:
		std::shared_ptr<Texture> texture;
		glm::vec2 uvCoords[4];
	};
}
