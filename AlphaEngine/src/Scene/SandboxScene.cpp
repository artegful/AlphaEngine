#include "SandboxScene.h"

#include "ECS/Entity.h"

#include "Core/Engine.h"
#include "Core/Window.h"
#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "Render/Renderer2D.h"
#include "Render/RenderCamera.h"
#include "Render/ProjectionCamera.h"
#include "Render/RenderProperties2D.h"

#include "Resources/ResourceAllocator.hpp"

#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Components/SpriteComponent.h"

#include "Systems/CameraControllerSystem.h"
#include "Systems/SpriteRenderSystem.h"
#include "Render/RenderCommand.h"

namespace Alpha
{
	SandboxScene::SandboxScene() : 
		texture(ResourceAllocator<Texture>::Get("assets/images/test.jpg"))
	{

	}

	void SandboxScene::Open()
	{
		Entity cameraEntity = CreateEntity("Camera");

		ProjectionCamera projection(Engine::Get()->GetWindow().GetWidth() / 300.0f, Engine::Get()->GetWindow().GetHeight() / 300.0f);
		cameraEntity.AddComponent<CameraComponent>(projection);

		renderCamera = std::make_unique<RenderCamera>(cameraEntity.GetComponent<CameraComponent>(), cameraEntity.GetComponent<TransformComponent>());

		std::shared_ptr<Texture> texture = ResourceAllocator<Texture>::Get("assets/images/dino.png");

		for (int x = -10; x <= 10; x++)
		{
			for (int y = -10; y <= 10; y++)
			{
				Entity entity = CreateEntity();

				auto& spriteComponent = entity.AddComponent<SpriteComponent>();
				spriteComponent.Sprite = Sprite::CreateFromCount(texture, { 1, 1 }, { 2, 2 });

				auto& transformComponent = entity.GetComponent<TransformComponent>();

				transformComponent.Transform.Position = { x, y, 0.0f };
				transformComponent.Transform.Rotation.z = 45.0f;
			}
		}

		sceneSystems.push_back(new SpriteRenderSystem(registry));
		sceneSystems.push_back(new CameraControllerSystem(registry));

		for (auto system : sceneSystems)
		{
			system->Start();
		}

		Renderer2D::Initialize();
	}

	void SandboxScene::Update(float deltaTime)
	{
		Renderer2D::ResetStats();

		RenderCommand::Clear();
		Scene::Update(deltaTime);
	}
}