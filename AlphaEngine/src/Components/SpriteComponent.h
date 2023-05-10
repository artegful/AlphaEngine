#pragma once

#include "glm/vec2.hpp"
#include "glm/vec4.hpp"
#include <memory>
#include <string>

namespace Alpha
{
	class Sprite;

	struct SpriteComponent
	{
		glm::vec4 Color { 1.0f, 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Alpha::Sprite> Sprite;

		inline std::string GetPath() const { return path; } 
		void SetPath(std::string newPath);
		void SetPathWithUVs(std::string newPath, const glm::vec2* uvs);

	private:
		std::string path;
	};
}