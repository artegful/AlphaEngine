#include "Scene.h"

#include "ECS/Entity.h"
#include "ECS/System.h"
#include "Components/NameComponent.h"
#include "Components/TransformComponent.h"
#include "Events/Event.h"

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

	void Scene::OnEvent(Event& event)
	{
		for (auto system : sceneSystems)
		{
			system->OnEvent(event);
		}
	}

	Entity Scene::CreateEntity()
	{
		return CreateEntity("Entity (" + std::to_string(amountOfUnnamedEntities++) + ")");
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		entt::entity handle = registry.create();

		registry.emplace<TransformComponent>(handle);
		registry.emplace<NameComponent>(handle, name);

		return Entity(this, handle);
	}

	void Scene::DestroyEntity(const Entity& entity)
	{
		registry.destroy(entity.handle);
	}

	std::vector<Entity> Scene::GetAllEntities()
	{
		std::vector<Entity> entities;

		registry.each([&](entt::entity handle)
			{
				entities.push_back(Entity(this, handle));
			});

		return entities;
	}
}
