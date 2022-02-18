#pragma once

#include <vector>
#include <memory>

namespace Alpha
{
	class Scene;

	struct Event;

	class SceneManager
	{
	public:
		SceneManager();

		void ChangeScene(int id);
		void Update(float deltaTime);
		void OnEvent(Event& event);

		Scene* GetCurrentScene();

	private:
		std::vector<Scene*> scenes;

		Scene* currentScene;
	};
}

