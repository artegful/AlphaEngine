#pragma once

#include <chrono>

#include "Core/Core.h"
#include "LayerStack.h"
#include "Window.h"
#include "Scene/SceneManager.h"

namespace Alpha
{
	struct Config;
	struct Event;

	class Engine
	{
	public:
		Engine(const Config& config);

		void Run();
		LayerStack& GetLayerStack();
		Window& GetWindow();

		static Engine* Get();

	private:
		static Engine* Instance;
		Window window;
		LayerStack layerStack;

		std::chrono::time_point<std::chrono::steady_clock> previousTime;
		float deltaTime = 0;
		bool isImGuiEnabled;

		void UpdateDeltaTime();
		void UpdateImGui();
		void OnEvent(Event& event);
	};
}


