#include "Engine.h"

#include <chrono>

#include "Core.h"
#include "Config.h"
#include "Controls/Input.h"
#include "Render/RenderCommand.h"
#include "Render/RendererAPI.h"

namespace Alpha
{
	Engine::Engine(const Config& config) :
		window(config.Width, config.Height),
		sceneManager{ }
	{
		RenderCommand::SetAPI(config.RenderApi);

		window.Initialize();
		sceneManager.ChangeScene(0);
		RenderCommand::SetClearColor({1.0f, 0.0f, 0.0f, 1.0f});

		previousTime = std::chrono::steady_clock::now();
	}

	void Engine::Run()
	{
		while (!window.ShouldClose())
		{
			UpdateDeltaTime();

			window.Update();
			sceneManager.Update(deltaTime);

			window.SwapBuffers();

			Input::EndFrame();
		}
	}

	void Engine::UpdateDeltaTime()
	{
		auto now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - previousTime).count();
		previousTime = now;
	}
}
