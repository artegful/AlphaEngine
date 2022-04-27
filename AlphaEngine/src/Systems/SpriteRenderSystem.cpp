#include "SpriteRenderSystem.h"

#include "Render/RenderCamera.h"
#include "Render/Renderer2D.h"

#include "Events/WindowResizedEvent.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"

namespace Alpha
{
	SpriteRenderSystem::SpriteRenderSystem(SceneManager* sceneManager) : System(sceneManager)
	{ }

	void SpriteRenderSystem::Start()
	{
		Renderer2D::Initialize();
	}

	void SpriteRenderSystem::Update(float deltaTime)
	{
		Renderer2D::ResetStats();

		auto view = GetRegistry().view<TransformComponent, CameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			RenderScene({ camera, transform });
		}
	}

	void SpriteRenderSystem::RenderScene(const RenderCamera& camera)
	{
		Renderer2D::BeginScene(camera);

		auto view = GetRegistry().view<TransformComponent, SpriteComponent>();
		for (auto& sprite : view)
		{
			auto [spriteTransform, spriteComponent] = view.get<TransformComponent, SpriteComponent>(sprite);

			Renderer2D::DrawQuad({ .Position = spriteTransform.Transform.Position, .Size = spriteTransform.Transform.Scale, .RotationAngle = glm::radians(spriteTransform.Transform.Rotation.z), .Sprite = spriteComponent.Sprite, .Color = spriteComponent.Color });
		}

		Renderer2D::EndScene();
	}

}

