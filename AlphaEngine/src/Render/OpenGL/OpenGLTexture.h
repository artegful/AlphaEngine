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

		void Bind(int slot = 0) override;
		void Unbind() override;

		int GetWidth() const override;
		int GetHeight() const override;

	private:
		static const std::unordered_map<int, GLenum> ChannelsToFormat;

		std::string name;
		GLuint textureId;
		int width;
		int height;
		int channels;
	};
}

