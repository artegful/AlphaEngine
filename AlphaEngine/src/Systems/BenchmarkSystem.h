#pragma once

#include "ECS/SceneSystem.h"

namespace Alpha
{
	class BenchmarkSystem : public SceneSystem
	{
	public:
		explicit BenchmarkSystem(Alpha::Scene* scene);

		void Start() override;
		void Update(float deltaTime) override;

		RTTR_ENABLE(SceneSystem)
	};
}
