#pragma once

#include "Events/Event.h"

namespace entt
{
	enum class entity : uint32_t;

	template<typename>
	class basic_registry;

	using registry = basic_registry<entt::entity>;
}

namespace Alpha
{
	class SceneManager;
	class Scene;

	class SceneSystem
	{
	public:
		SceneSystem(Scene* scene);
		virtual ~SceneSystem() = default;

		virtual void Start() { }
		virtual void Update(float deltaTime) = 0;
		virtual void OnEvent(Event& event) { };

	protected:
		entt::registry& GetRegistry() const;
		Scene* scene;
	};
}


