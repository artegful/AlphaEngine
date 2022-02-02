#pragma once

#include <glm/gtx/quaternion.hpp>

namespace Alpha
{
	struct Transform
	{
		glm::vec3 Position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		glm::vec3 Scale = { 1.0f, 1.0f, 1.0f };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const glm::vec3 & translation) :
			Position(translation)
		{ }

		glm::mat4 GetTransformMatrix() const
		{
			glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Position)
				* glm::scale(glm::mat4(1.0f), Scale);
		}
	};
}