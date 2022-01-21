#pragma once

#include <chrono>

#include "Core/Core.h"
#include "Window.h"
#include "Scene/SceneManager.h"

namespace Alpha
{
	struct Config;

	class Engine
	{
	public:
		Engine(const Config& config);

		void Run();

	private:
		Window window;
		SceneManager sceneManager;

		std::chrono::time_point<std::chrono::steady_clock> previousTime;
		float deltaTime = 0;

		void UpdateDeltaTime();
	};
}


