#pragma once

#include <vector>

#include "entt/entt.hpp"

class b2World;

namespace Alpha
{
	class Entity;
	class SceneSystem;

	struct Event;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void Open();
		virtual void Start();
		virtual void Stop();
		virtual void Update(float deltaTime);
		virtual void Close() { };
		virtual void OnEvent(Event& event);

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);
		void DestroyEntity(const Entity& entity);
		std::vector<Entity> GetAllEntities();

	protected:
		entt::registry registry;
		std::vector<SceneSystem*> sceneSystems;

	private:
		size_t amountOfUnnamedEntities = 0;
		b2World* physicsWorld;

		friend class Entity;
		friend class System;
		friend class SceneSystem;
		friend class SceneSerializer;
	};
}


