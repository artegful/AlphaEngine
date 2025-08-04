#pragma once

#include "ECS/SceneSystem.h"

namespace Alpha
{
	class OrbitSystem : public SceneSystem
	{
	public:
		explicit OrbitSystem(Alpha::Scene* scene);

		void Open() override;
		void Start() override;
		void Update(float deltaTime) override;
		float GetRandom(float range);


		RTTR_ENABLE(SceneSystem)
	};
}