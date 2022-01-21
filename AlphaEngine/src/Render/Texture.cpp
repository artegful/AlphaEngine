#include "Texture.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "stb_image.h"

namespace Alpha
{
	const std::unordered_map<int, GLenum> Texture::ChannelsToFormat
	{
		{ 3, GL_RGB  },
		{ 4, GL_RGBA }
	};

	Texture::Texture(const char* filePath)
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(filePath, &width, &height, &channels, 0);

		if (!data) 
		{
			throw std::invalid_argument(std::string("cannot load texture from ") + filePath);
		}

		if (ChannelsToFormat.find(channels) == ChannelsToFormat.end())
		{
			throw std::invalid_argument(std::string("cannot use texture with ") + std::to_string(channels) + " channels");
		}

		glTexImage2D(GL_TEXTURE_2D, 0, ChannelsToFormat.at(channels), width, height, 0, 
			ChannelsToFormat.at(channels), GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::Use() const
	{
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void Texture::UseInSlot(int slotNumber) const
	{
		glActiveTexture(GL_TEXTURE0 + slotNumber);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void Texture::Detach() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

