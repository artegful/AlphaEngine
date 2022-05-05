#include "Engine.h"

#include <chrono>

#include "Core.h"
#include "Config.h"
#include "Layer.h"
#include "Window.h"
#include "GlfwWindow.h"
#include "Layers/GameLayer.h"
#include "Layers/ImGuiLayer.h"
#include "Events/Event.h"
#include "Controls/Input.h"
#include "Render/RenderCommand.h"
#include "Render/RendererAPI.h"
#include "Render/Renderer2D.h"

#include "rttr/registration.h"
#include "rttr/constructor.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/OrthoCameraComponent.h"

#include "ECS/Script.h"

#include "Reflection/MetadataType.h"
#include "Reflection/MetadataVectorUsage.h"

#include "Reflection/Registration.h"

#include "rttr/constructor.h"

namespace Alpha
{
	Engine* Engine::Instance = nullptr;

	Engine::Engine(const Alpha::Config& config) :
		isImGuiEnabled(config.IsImGuiEnabled),
		window(nullptr)
	{
		Instance = this;
		RenderCommand::SetAPI(config.RenderApi);
		window.reset(new GlfwWindow(config.Width, config.Height));
   	}

	void Engine::SetCustomWindow(const std::shared_ptr<Window>& customWindow)
	{
		window = customWindow;
	}

	void Engine::Run()
	{
		while (!window->ShouldClose())
		{
			Update();
		}
	}

	void Engine::Update()
	{
		UpdateDeltaTime();
		window->Update();

		for (auto layer : layerStack)
		{
			layer->Update(deltaTime);
		}

		if (isImGuiEnabled)
		{
			UpdateImGui();
		}

		window->SwapBuffers();
		Input::EndFrame();
	}

	LayerStack& Engine::GetLayerStack()
	{
		return layerStack;
	}

	Window& Engine::GetWindow()
	{
		return *window;
	}

	GameLayer& Engine::GetGameLayer()
	{
		return *gameLayer;
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

	void Engine::UpdateImGui()
	{
		ImGuiLayer::Begin();

		for (auto layer : layerStack)
		{
			layer->OnImGui();
		}

		ImGuiLayer::End();
	}

	void Engine::Initialize()
	{
		window->Initialize();
		window->SetEventCallback(EVENT_BIND(OnEvent));
		RenderCommand::Initialize();

		previousTime = std::chrono::steady_clock::now();

		gameLayer = new GameLayer();
		layerStack.AddLayer(gameLayer);

		if (isImGuiEnabled)
		{
			layerStack.AddOverlay(new ImGuiLayer());
		}
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
