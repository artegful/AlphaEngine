#pragma once

#include <vector>
#include "ECS/System.h"
#include "Render/Model.h"
#include <Render/Skybox.h>

namespace Alpha
{
	struct WindowResizedEvent;
	class RenderCamera;

	class RenderSystem : public System
	{
	public:
		RenderSystem(SceneManager* scene);

		void Start() override;
		void Update(float deltaTime) override;
		void RenderScene(const RenderCamera& camera);

	private:
		constexpr static uint32_t MAX_POINT_LIGHTS = 5;
	};
}


