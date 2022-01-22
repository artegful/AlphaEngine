#include "GameLayer.h"

#include "Render//RenderCommand.h"

namespace Alpha
{
	void GameLayer::Open()
	{
		sceneManager.ChangeScene(0);
		RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
	}

	void GameLayer::Close()
	{ }

	void GameLayer::Update(float deltaTime)
	{
		sceneManager.Update(deltaTime);
	}
}
