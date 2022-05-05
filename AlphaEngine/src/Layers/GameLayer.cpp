#include "GameLayer.h"

#include "Core/Core.h"
#include "Render/RenderCommand.h"
#include "Scene/Scene.h"
#include "Systems/CameraControllerSystem.h"
#include "Systems/SpriteRenderSystem.h"

namespace Alpha
{
	GameLayer::GameLayer() :
		mode(GameMode::Game),
		sceneRenderer(&sceneManager),
		cameraController(&sceneManager),
		editorCamera(16.0f / 9.0f, 90),
		editorCameraTransform(Transform({ 0, 0, 20 }))
	{ }

	void GameLayer::Open()
	{
		sceneManager.ChangeScene(new Scene());
		RenderCommand::SetClearColor({ 0.5f, 0.5f, 0.5f, 1.0f });

		sceneRenderer.Start();
		cameraController.Start();
	}

	void GameLayer::Close()
	{ }

	void GameLayer::Update(float deltaTime)
	{
		switch (mode)
		{
		case GameMode::Game:
			UpdateGame(deltaTime);
			break;
		case GameMode::Editor:
			UpdateEditor(deltaTime);
			break;
		default:
			AL_ENGINE_ASSERT(false, "Unknown game layer mode");
			break;
		}
	}

	void GameLayer::OnEvent(Event& event)
	{
		sceneRenderer.OnEvent(event);
		cameraController.OnEvent(event);

		sceneManager.OnEvent(event);
	}

	void GameLayer::SetMode(GameMode mode)
	{
		bool isChanged = this->mode != mode;

		this->mode = mode;

		if (isChanged)
		{
			switch (this->mode)
			{
			case GameMode::Editor:
				sceneManager.Stop();
				break;

			case GameMode::Game:
				sceneManager.Start();
				break;
			}
		}

	}

	SceneManager& GameLayer::GetSceneManager()
	{
		return sceneManager;
	}

	void GameLayer::UpdateGame(float deltaTime)
	{
		sceneRenderer.Update(deltaTime);

		sceneManager.Update(deltaTime);
	}

	void GameLayer::UpdateEditor(float deltaTime)
	{
		sceneRenderer.RenderScene({ editorCamera, editorCameraTransform });
		cameraController.UpdateCamera(deltaTime, editorCameraTransform, editorCamera);
	}
}
