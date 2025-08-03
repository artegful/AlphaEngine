#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Alpha
{
	class Scene;

	struct Event;

	class SceneManager
	{
	public:
		SceneManager();

		void ChangeScene(Scene* scene);
		void ChangeScene(const std::string& path);
		void Start();
		void Stop();
		void Update(float deltaTime);
		void OnEvent(Event& event);
		bool IsStarted() const;

		Scene* GetCurrentScene();

	private:
		std::unique_ptr<Scene> currentScene;
		bool isStarted;
	};
}

