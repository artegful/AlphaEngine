#pragma once

#include "ECS/SceneSystem.h"

namespace Alpha
{
	class ScriptSystem : public SceneSystem
	{
	public:
		explicit ScriptSystem(Scene* scene);

		void Start() override;
		void Update(float deltaTime) override;
	};
}