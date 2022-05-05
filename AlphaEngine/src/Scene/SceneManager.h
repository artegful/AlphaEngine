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
		~SceneManager();

		void ChangeScene(Scene* scene);
		void Start();
		void Stop();
		void Update(float deltaTime);
		void OnEvent(Event& event);

		Scene* GetCurrentScene();

	private:
		Scene* currentScene;
	};
}

