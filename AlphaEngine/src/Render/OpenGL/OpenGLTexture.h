#pragma once

#include <unordered_map>

#include "Render/Texture.h"
#include "GL/glew.h"

namespace Alpha
{
	class OpenGLTexture : public Texture
	{
	public:
		OpenGLTexture(const std::string& filePath);
		OpenGLTexture(size_t width, size_t height);

		void Bind(int slot = 0) override;
		void Unbind() override;

		void SetData(void* data, size_t size, int channels) override;

		int GetWidth() const override;
		int GetHeight() const override;
		std::string GetPath() const override;

		bool operator==(const Texture& texture) override;

	private:
		OpenGLTexture();

		static const std::unordered_map<int, GLenum> ChannelsToFormat;

		std::string name;
		std::string path;
		GLuint id;
		int width;
		int height;
		int channels;
	};
}

