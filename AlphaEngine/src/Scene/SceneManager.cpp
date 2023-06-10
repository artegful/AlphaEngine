#include "SceneManager.h"

#include <stdexcept>

#include "Core/Core.h"
#include "Scene.h"
#include "Events/Event.h"
#include "SceneSerializer.h"

namespace Alpha
{
	SceneManager::SceneManager() :
		currentScene(nullptr),
		isStarted(false)
	{ }

	SceneManager::~SceneManager()
	{
		if (currentScene)
		{
			delete currentScene;
		}
	}

	void SceneManager::ChangeScene(const std::string& path)
	{
		Alpha::Scene* scene = new Alpha::Scene();
		Alpha::SceneSerializer serializer(scene);
		serializer.Deserialize(path);

		ChangeScene(scene);
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

		if (isStarted)
		{
			currentScene->Start();
		}
	}

	void SceneManager::Start()
	{
		currentScene->Start();
		isStarted = true;
	}

	void SceneManager::Stop()
	{
		currentScene->Stop();
		isStarted = false;
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

	bool SceneManager::IsStarted() const
	{
		return isStarted;
	}
}

