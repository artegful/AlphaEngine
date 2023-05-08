#pragma once

#include <vector>
#include "ECS/System.h"
#include "Render/Model.h"

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

		std::shared_ptr<Model> model;
	};
}


