#include "SceneSystem.h"

#include "Scene/Scene.h"

namespace Alpha
{
	SceneSystem::SceneSystem(Scene* scene) :
		scene(scene)
	{ }

	entt::registry& SceneSystem::GetRegistry() const
	{
		return scene->registry;
	}
}

