#pragma once

#include <vector>

#include "Core/Layer.h"
#include "GameMode.h"
#include "Scene/SceneManager.h"
#include "Systems/CameraControllerSystem.h"
#include "Systems/RenderSystem.h"
#include "Render/PerspectiveCamera.h"
#include "Render/RenderCamera.h"

namespace Alpha
{
	class System;

	class GameLayer : public Layer
	{
	public:
		GameLayer(GameMode mode);

		void Open() override;
		void Close() override;
		void Update(float deltaTime) override;
		void OnEvent(Event& event) override;

		void SetMode(GameMode mode);

		SceneManager& GetSceneManager();

	private:
		GameMode mode;

		SceneManager sceneManager;
		RenderSystem sceneRenderer;
		CameraControllerSystem cameraController;

		PerspectiveCamera editorCamera;
		Transform editorCameraTransform;

		void UpdateGame(float deltaTime);
		void UpdateEditor(float deltaTime);
		void SetModeInternal(GameMode mode);
	};
}


