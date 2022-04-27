#pragma once

#include <vector>

#include "entt/entt.hpp"

namespace Alpha
{
	class Entity;
	class System;

	struct Event;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void Open();
		virtual void Update(float deltaTime);
		virtual void Close() { };
		virtual void OnEvent(Event& event);

		Entity CreateEntity();
		Entity CreateEntity(const std::string& name);
		void DestroyEntity(const Entity& entity);
		std::vector<Entity> GetAllEntities();

	protected:
		entt::registry registry;
		std::vector<System*> sceneSystems;

	private:
		size_t amountOfUnnamedEntities = 0;

		friend class Entity;
		friend class System;
		friend class SceneSerializer;
	};
}


