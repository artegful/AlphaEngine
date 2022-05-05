#pragma once

#include <chrono>

#include "Core/Core.h"
#include "LayerStack.h"
#include "Scene/SceneManager.h"

namespace Alpha
{
	struct Config;
	struct Event;

	class Window;
	class GameLayer;

	class Engine
	{
	public:
		Engine(const Config& config);

		void SetCustomWindow(const std::shared_ptr<Window>& customWindow);

		void Initialize();
		void Run();
		void Update();
		LayerStack& GetLayerStack();
		Window& GetWindow();
		GameLayer& GetGameLayer();

		static Engine* Get();

	private:
		static Engine* Instance;

		std::shared_ptr<Alpha::Window> window;
		LayerStack layerStack;
		GameLayer* gameLayer;

		std::chrono::time_point<std::chrono::steady_clock> previousTime;
		float deltaTime = 0;
		bool isImGuiEnabled;

		void UpdateDeltaTime();
		void UpdateImGui();
		void OnEvent(Event& event);
	};
}


