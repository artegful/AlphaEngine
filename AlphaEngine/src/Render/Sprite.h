#pragma once

#include <memory>
#include "glm/glm.hpp"

#include "Texture.h"

namespace Alpha
{
	class Sprite
	{
	public:
		Sprite(const std::shared_ptr<Texture> texture, const glm::vec2 uvs[4]);
		Sprite(const std::shared_ptr<Texture> texture);

		const glm::vec2* GetUvs() const;
		std::shared_ptr<Texture> GetTexture() const;
		bool HasTexture() const;

		static std::shared_ptr<Sprite> CreateFromSize(const std::shared_ptr<Texture> spriteSheet, const glm::ivec2 spriteCoodsInCells,
			const glm::ivec2 cellSizeInPixels, const glm::i8vec2 spriteSizeInCells = { 1, 1 });
		static std::shared_ptr<Sprite> CreateFromCount(const std::shared_ptr<Texture> spriteSheet, const glm::ivec2 spriteCoodsInCells,
			const glm::ivec2 amountOfCells, const glm::i8vec2 spriteSizeInCells = { 1, 1 });
		static std::shared_ptr<Sprite> Create(const std::shared_ptr<Texture> texture, const glm::vec2 uvs[4]);

	private:
		std::shared_ptr<Texture> texture;
		glm::vec2 uvCoords[4]
		{ 
			glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f),
			glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) 
		};
	};
}