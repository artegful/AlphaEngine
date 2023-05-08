#include "SpriteRenderSystem.h"

#include "entt/entt.hpp"

#include "Render/RenderCamera.h"
#include "Render/Renderer2D.h"
#include "Render/Renderer3D.h"

#include "Events/WindowResizedEvent.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/OrthoCameraComponent.h"
#include <Components/ModelComponent.h>
#include "Resources/ResourceAllocator.hpp"
#include <Components/NameComponent.h>

namespace Alpha
{
	SpriteRenderSystem::SpriteRenderSystem(SceneManager* sceneManager) : System(sceneManager)
	{ }

	void SpriteRenderSystem::Start()
	{
		Renderer2D::Initialize();
		Renderer3D::Initialize();
	}

	void SpriteRenderSystem::Update(float deltaTime)
	{
		Renderer2D::ResetStats();

		auto view = GetRegistry().view<TransformComponent, OrthoCameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, OrthoCameraComponent>(entity);

			RenderScene({ camera, transform });
		}
	}

	void SpriteRenderSystem::RenderScene(const RenderCamera& camera)
	{
		Renderer3D::BeginScene(camera);

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
	}

}

