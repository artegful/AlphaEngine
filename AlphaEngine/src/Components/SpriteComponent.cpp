#include "SpriteComponent.h"

#include <filesystem>
#include "Resources/ResourceAllocator.hpp"
#include "Render/Texture.h"
#include "Render/Sprite.h"

namespace Alpha
{
	void SpriteComponent::SetPath(std::string newPath)
	{
		if (!std::filesystem::exists(newPath))
		{
			return;
		}

		path = newPath;

		std::shared_ptr<Texture> texture = ResourceAllocator<Texture>::Get(path);
		Sprite = Sprite::Create(texture);
	}

	void SpriteComponent::SetPathWithUVs(std::string newPath, const glm::vec2* uvs)
	{
		if (!std::filesystem::exists(newPath))
		{
			return;
		}

		path = newPath;

		std::shared_ptr<Texture> texture = ResourceAllocator<Texture>::Get(path);
		Sprite = Sprite::Create(texture, uvs);
	}

}