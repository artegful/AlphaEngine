#include "RenderSystem.h"

#include "entt/entt.hpp"

#include "Render/RenderCamera.h"
#include "Render/Renderer2D.h"
#include "Render/Renderer3D.h"
#include "Render/RenderCommand.h"

#include "Events/WindowResizedEvent.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/PerspectiveCameraComponent.h"
#include <Components/ModelComponent.h>
#include "Resources/ResourceAllocator.hpp"
#include <Components/NameComponent.h>
#include <Components/PointLightComponent.h>

namespace Alpha
{
	RenderSystem::RenderSystem(SceneManager* sceneManager) : System(sceneManager)
	{ }

	void RenderSystem::Start()
	{
		Renderer2D::Initialize();
		Renderer3D::Initialize();
	}

	void RenderSystem::Update(float deltaTime)
	{
		Renderer2D::ResetStats();
		RenderCommand::Clear();

		auto view = GetRegistry().view<TransformComponent, PerspectiveCameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, PerspectiveCameraComponent>(entity);

			RenderScene({ camera, transform });
		}
	}

	void RenderSystem::RenderScene(const RenderCamera& camera)
	{
		Renderer3D::BeginScene(camera);

		auto lightView = GetRegistry().view<TransformComponent, PointLightComponent>();
		int lightsFound = 0;
		for (auto& light : lightView)
		{
			auto [transform, lightComponent] = lightView.get<TransformComponent, PointLightComponent>(light);

			Renderer3D::BindPointLight(transform, lightComponent.Light);
		}

		Renderer3D::FinishBindingPointLights();

		auto modelView = GetRegistry().view<TransformComponent, ModelComponent>();
		for (auto& model : modelView)
		{
			auto [transform, modelComponent] = modelView.get<TransformComponent, ModelComponent>(model);

			if (modelComponent.Model != nullptr)
			{
				Renderer3D::DrawModel(*modelComponent.Model, transform);
			}
		}

		Renderer3D::EndScene();

		Renderer2D::BeginScene(camera);

		auto view = GetRegistry().view<TransformComponent, SpriteComponent>();
		for (auto& sprite : view)
		{
			auto [spriteTransform, spriteComponent] = view.get<TransformComponent, SpriteComponent>(sprite);

			Renderer2D::DrawQuad({ .Transform = spriteTransform, .Sprite = spriteComponent.Sprite, 
				.Color = spriteComponent.Color });
		}

		Renderer2D::EndScene();

		Renderer3D::DrawSkybox(camera);
	}

}

