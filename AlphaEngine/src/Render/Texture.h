#pragma once

#include <unordered_map>

#include "GL/glew.h"

namespace Alpha
{
	class Texture
	{
	public:
		Texture(const char* filePath);

		void Use() const;
		void UseInSlot(int slotNumber) const;
		void Detach() const;

	private:
		static const std::unordered_map<int, GLenum> ChannelsToFormat;

		GLuint textureId;
		int width;
		int height;
		int channels;
	};
}

