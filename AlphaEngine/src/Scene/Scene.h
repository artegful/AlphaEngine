#pragma once

#include <vector>

#include "entt/entt.hpp"

namespace Alpha
{
	class Entity;
	class System;

	class Scene
	{
	public:
		Scene();
		virtual ~Scene() = default;

		virtual void Open() { };
		virtual void Update(float deltaTime);
		virtual void Close() { };

		Entity CreateEntity();

	protected:
		entt::registry registry;
		std::vector<System*> sceneSystems;

		friend class Entity;
	};
}


