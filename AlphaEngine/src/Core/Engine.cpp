#include "Engine.h"

#include <chrono>

#include "Core.h"
#include "Config.h"
#include "Layer.h"
#include "Events/Event.h"
#include "Controls/Input.h"
#include "Render/RenderCommand.h"
#include "Render/RendererAPI.h"

namespace Alpha
{
	Engine* Engine::Instance = nullptr;

	Engine::Engine(const Config& config) :
		window(config.Width, config.Height, EVENT_BIND(OnEvent))
	{
		Instance = this;
		RenderCommand::SetAPI(config.RenderApi);

		window.Initialize();

		previousTime = std::chrono::steady_clock::now();
	}

	void Engine::Run()
	{
		while (!window.ShouldClose())
		{
			UpdateDeltaTime();
			window.Update();

			for (auto layer : layerStack)
			{
				layer->Update(deltaTime);
			}

			window.SwapBuffers();
			Input::EndFrame();
		}
	}

	LayerStack& Engine::GetLayerStack()
	{
		return layerStack;
	}

	Engine* Engine::Get()
	{
		AL_ASSERT(Instance, "You must construct engine instance");

		return Instance;
	}

	void Engine::UpdateDeltaTime()
	{
		auto now = std::chrono::steady_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(now - previousTime).count();
		previousTime = now;
	}

	void Engine::OnEvent(Event& event)
	{
		for (auto it = layerStack.rbegin(); it != layerStack.rend(); it++)
		{
			if (event.IsDispatched)
			{
				return;
			}

			(*it)->OnEvent(event);
		}

		Input::OnEvent(event);
	}
}
