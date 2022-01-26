#include "OpenGLTexture.h"

#include "Core/Core.h"
#include "stb_image.h"
#include "Utils/Utils.h"

namespace Alpha
{
	const std::unordered_map<int, GLenum> OpenGLTexture::ChannelsToFormat
	{
		{ 3, GL_RGB  },
		{ 4, GL_RGBA }
	};

	OpenGLTexture::OpenGLTexture(const std::string& path) : 
		name(Utils::GetNameFromPath(path))
	{
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.data(), &width, &height, &channels, 0);

		AL_ASSERT(data, std::string("Error reading texture ") + name + " from file " + path);
		AL_ASSERT(ChannelsToFormat.contains(channels), std::string("Texture with ") + std::to_string(channels) + " channels is not supported");

		glTexImage2D(GL_TEXTURE_2D, 0, ChannelsToFormat.at(channels), width, height, 0, 
			ChannelsToFormat.at(channels), GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::Bind(int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, textureId);
	}

	void OpenGLTexture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	int OpenGLTexture::GetWidth() const
	{
		return width;
	}
	int OpenGLTexture::GetHeight() const
	{
		return height;
	}
}

