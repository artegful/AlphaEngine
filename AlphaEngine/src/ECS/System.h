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

	class System
	{
	public:
		System(SceneManager* scene);
		virtual ~System() = default;

		virtual void Start() { }
		virtual void Update(float deltaTime) = 0;
		virtual void OnEvent(Event& event) { };

	protected:
		entt::registry& GetRegistry() const;
		Scene* GetCurrentScene() const;

	private:
		SceneManager* sceneManager;
	};
}


