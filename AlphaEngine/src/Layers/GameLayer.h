#pragma once

#include "Core/Layer.h"
#include "Scene/SceneManager.h"

namespace Alpha
{
	class GameLayer : public Layer
	{
	public:
		void Open() override;
		void Close() override;
		void Update(float deltaTime) override;
		void OnEvent(Event& event) override;

		SceneManager& GetSceneManager();

	private:
		SceneManager sceneManager;
	};
}


