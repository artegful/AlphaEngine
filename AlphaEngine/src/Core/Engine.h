#pragma once

#include <chrono>

#include "Core/Core.h"
#include "LayerStack.h"
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
		LayerStack& GetLayerStack();
		static Engine* Get();

	private:
		static Engine* Instance;
		Window window;
		LayerStack layerStack;

		std::chrono::time_point<std::chrono::steady_clock> previousTime;
		float deltaTime = 0;

		void UpdateDeltaTime();
	};
}


