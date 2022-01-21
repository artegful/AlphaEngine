#include "Scene.h"

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Components/TransformComponent.h"

namespace Alpha
{
	Scene::Scene() :
		registry{},
		sceneSystems{}
	{ }

	void Scene::Update(float deltaTime)
	{
		for (auto system : sceneSystems)
		{
			system->Update(deltaTime);
		}
	}

	Entity Scene::CreateEntity()
	{
		entt::entity handle = registry.create();

		registry.emplace<TransformComponent>(handle);

		return Entity(this, handle);
	}
}
