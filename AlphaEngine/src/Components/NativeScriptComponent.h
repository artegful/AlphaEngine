#pragma once

#include <functional>
#include "Core/Core.h"
#include "ECS/Script.h"

namespace Alpha
{
	struct NativeScriptComponent
	{
		NativeScriptComponent() = default;
		~NativeScriptComponent() = default;

		Script* script;

		template<typename T>
		void SetScript()
		{
			instantiatePtr = [](const Entity& entity, entt::registry& registry) { return (Script*) new T(entity, registry); };
		}

		void Start(const Entity& entity, entt::registry& registry)
		{
			AL_ASSERT(instantiatePtr, "No script in the script component!");
			script = instantiatePtr(entity, registry);

			script->Start();
		}

		void Update(float deltaTime)
		{
			script->Update(deltaTime);
		}

	private:
		std::function<Script* (const Entity&, entt::registry&)> instantiatePtr = nullptr;
	};
}
