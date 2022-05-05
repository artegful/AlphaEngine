#pragma once

#include "rttr/type.h"
#include "Entity.h"
#include "Components/TransformComponent.h"
#include "Core/Transform.h"

namespace Alpha
{
	class Script
	{
	public:
		Script(const Entity& entity, entt::registry& registry) : 
			entity(entity), registry(registry)
		{ }
		virtual ~Script() = default;

		virtual void Start() { }
		virtual void Update(float deltaTime) { }
		virtual void OnDestroy() { }

		int Value;

		template<typename T>
		T& GetComponent();

	protected:
		entt::registry& registry;

	private:
		Entity entity;

		RTTR_ENABLE()
	};

	template<typename T>
	T& Script::GetComponent()
	{
		return entity.GetComponent<T>();
	}
}