#pragma once

#include "Scene.h"
#include "Render/Camera.h"

namespace Alpha
{
	class Texture;

	class SandboxScene : public Scene
	{
	public:
		SandboxScene();

		void Open() override;
		void Update(float deltaTime) override;

	private:
		Camera camera;

		std::shared_ptr<Texture> texture;
	};
}

