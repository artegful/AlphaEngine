#pragma once

#include "entt/entt.hpp"
#include "Events/Event.h"

namespace Alpha
{
	class SceneManager;

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

	private:
		SceneManager* sceneManager;
	};
}


