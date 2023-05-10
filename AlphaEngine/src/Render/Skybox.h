#pragma once

#include <array>
#include <memory>
#include "Texture.h"
#include "VertexArray.h"

namespace Alpha
{
	class Skybox
	{
	public:
		Skybox(const std::array<std::string, 6> texturePaths);

		void Draw();

	private:
		unsigned int cubemapId;
		std::shared_ptr<VertexArray> vertexArray;

		void LoadTextures(const std::array<std::string, 6> texturePaths);
	};
}