#include "SceneManager.h"

#include <stdexcept>

#include "Core/Core.h"
#include "Scene/SandboxScene.h"

namespace Alpha
{
	SceneManager::SceneManager() :
		scenes{ new SandboxScene() },
		currentScene()
	{
		//TODO deserialize scene
	}

	void SceneManager::ChangeScene(int id)
	{
		AL_ENGINE_ASSERT(id >= 0 && std::cmp_less(id, scenes.size()), "Scene id wasn't in valid range");

		if (currentScene)
		{
			currentScene->Close();
		}

		currentScene = scenes[id];

		currentScene->Open();
	}

	void SceneManager::Update(float deltaTime)
	{
		if (currentScene)
		{
			currentScene->Update(deltaTime);
		}
	}
}

