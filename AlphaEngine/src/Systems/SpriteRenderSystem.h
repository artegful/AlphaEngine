#pragma once

#include <vector>
#include "ECS/System.h"

namespace Alpha
{
	struct WindowResizedEvent;
	class RenderCamera;

	class SpriteRenderSystem : public System
	{
	public:
		SpriteRenderSystem(SceneManager* scene);

		void Start() override;
		void Update(float deltaTime) override;
		void RenderScene(const RenderCamera& camera);
	};
}


