#include "OpenGLTexture.h"

#include "Core/Core.h"
#include "stb_image.h"
#include "Utils/Utils.h"

using namespace std::string_literals;

namespace Alpha
{
	const std::unordered_map<int, GLenum> OpenGLTexture::ChannelsToFormat
	{
		{ 3, GL_RGB  },
		{ 4, GL_RGBA }
	};

	OpenGLTexture::OpenGLTexture(const std::string& path) : OpenGLTexture()
	{
		this->path = path;
		name = Utils::GetNameFromPath(path);

		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.data(), &width, &height, &channels, 0);

		AL_ASSERT(data, "Error reading texture "s + name + " from file " + path);
		AL_ASSERT(ChannelsToFormat.contains(channels), "Texture with "s + std::to_string(channels) + " channels is not supported");

		SetData(data, width * height * channels, channels);

		stbi_image_free(data);
	}

	OpenGLTexture::OpenGLTexture(size_t width, size_t height) : OpenGLTexture()
	{
		name = "UnnamedTexture";
		channels = 0;

		this->width = width;
		this->height = height;
	}

	OpenGLTexture::OpenGLTexture()
	{
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void OpenGLTexture::SetData(void* data, size_t size, int channels)
	{
		this->channels = channels;

		glTexImage2D(GL_TEXTURE_2D, 0, ChannelsToFormat.at(channels), width, height, 0,
			ChannelsToFormat.at(channels), GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture::Bind(int slot)
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, id);
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

	std::string OpenGLTexture::GetPath() const
	{
		return path;
	};


	bool OpenGLTexture::operator==(const Texture& texture)
	{
		return id == ((OpenGLTexture&)texture).id;
	}
}

