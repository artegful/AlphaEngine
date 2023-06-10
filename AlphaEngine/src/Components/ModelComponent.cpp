#include "ModelComponent.h"

#include "Render/Model.h"
#include "Resources/ResourceAllocator.hpp"

namespace Alpha
{
	void ModelComponent::SetPath(std::string path)
	{
		objPath = path;

		this->Model = ResourceAllocator<Alpha::Model>::Get(path);
	}
}

