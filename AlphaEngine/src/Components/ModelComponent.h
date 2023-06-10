#pragma once

#include <string>
#include "glm/vec2.hpp"
#include "Render/Model.h"

namespace Alpha
{
	struct ModelComponent
	{
		ModelComponent() = default;
		ModelComponent(const ModelComponent&) = default;

		inline std::string GetPath() const
		{
			return objPath;
		}

		void SetPath(std::string path);

		std::shared_ptr<Model> Model;

	private:
		std::string objPath;
	};
}