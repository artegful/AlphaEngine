#pragma once

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
			instantiatePtr = [](Entity& entity, entt::registry& registry) { return (Script*) new T(entity, registry); };
		}

		void Start(Entity& entity, entt::registry& registry)
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
		Script* (*instantiatePtr)(Entity& entity, entt::registry& registry) = nullptr;
	};
}
