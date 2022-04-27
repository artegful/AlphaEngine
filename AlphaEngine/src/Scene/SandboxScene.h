#pragma once

#include "Scene.h"

namespace Alpha
{
	class Texture;
	class RenderCamera;

	class SandboxScene : public Scene
	{
	public:
		SandboxScene() = default;

		void Open() override;
		void Update(float deltaTime) override;

	private:
		std::shared_ptr<Texture> texture;
		std::unique_ptr<RenderCamera> renderCamera;
	};
}

