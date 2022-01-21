#pragma once

#include "entt/entt.hpp"

#include "Scene/Scene.h"

namespace Alpha
{
	class Entity
	{
	public:
		Entity(Alpha::Scene* scene, entt::entity handle);

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			return scene->registry.emplace<T>(handle, std::forward<Args>(args)...);
		}

		template<typename T>
		void RemoveComponent()
		{
			scene->registry.remove<T>(handle);
		}

		template<typename T>
		T& GetComponent()
		{
			return scene->registry.get<T>(handle);
		}

		template<typename T>
		T& TryGetComponent()
		{
			return scene->registry.try_get<T>(handle);
		}

	private:
		Alpha::Scene *scene;
		entt::entity handle;
	};
}


