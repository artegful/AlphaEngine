#pragma once

#include <vector>
#include <memory>

namespace Alpha
{
	class Scene;

	class SceneManager
	{
	public:
		SceneManager();

		void ChangeScene(int id);
		void Update(float deltaTime);

	private:
		std::vector<Scene*> scenes;

		Scene* currentScene;
	};
}

