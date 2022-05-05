#include "ScriptSystem.h"

#include "entt/entt.hpp"
#include "Components/NativeScriptComponent.h"

namespace Alpha
{
	ScriptSystem::ScriptSystem(Scene* scene) : SceneSystem(scene)
	{ }

	void ScriptSystem::Start()
	{
		auto view = GetRegistry().view<NativeScriptComponent>();

		for (auto e : view)
		{
			auto& component = GetRegistry().get<NativeScriptComponent>(e);
			component.Start(Entity{ scene, e}, GetRegistry());
		}
	}

	void ScriptSystem::Update(float deltaTime)
	{
		auto view = GetRegistry().view<NativeScriptComponent>();

		for (auto e : view)
		{
			auto& component = GetRegistry().get<NativeScriptComponent>(e);
			component.Update(deltaTime);
		}
	}
}