#include "SceneManager.h"

#include <stdexcept>

#include "Core/Core.h"
#include "Scene.h"
#include "Events/Event.h"

namespace Alpha
{
	SceneManager::SceneManager() :
		currentScene(nullptr)
	{ }

	SceneManager::~SceneManager()
	{
		if (currentScene)
		{
			delete currentScene;
		}
	}

	void SceneManager::ChangeScene(Scene* scene)
	{
		if (currentScene)
		{
			currentScene->Close();
		}

		delete currentScene;
		currentScene = scene;

		currentScene->Open();
	}

	void SceneManager::Start()
	{
		currentScene->Start();
	}

	void SceneManager::Stop()
	{
		currentScene->Stop();
	}

	void SceneManager::Update(float deltaTime)
	{
		if (currentScene)
		{
			currentScene->Update(deltaTime);
		}
	}

	void SceneManager::OnEvent(Event& event)
	{
		currentScene->OnEvent(event);
	}

	Scene* SceneManager::GetCurrentScene()
	{
		return currentScene;
	}
}

