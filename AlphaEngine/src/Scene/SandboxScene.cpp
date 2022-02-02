#include "SandboxScene.h"

#include "ECS/Entity.h"

#include "Core/Engine.h"
#include "Render/Texture.h"
#include "Render/Sprite.h"
#include "Render/Renderer2D.h"
#include "Render/SpriteProperties.h"

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
		camera(Engine::Get()->GetWindow().GetWidth() / 300.0f, Engine::Get()->GetWindow().GetHeight() / 300.0f),
		texture(ResourceAllocator<Texture>::Get("assets/images/test.jpg"))
	{

	}

	void SandboxScene::Open()
	{
		Entity cameraEntity = CreateEntity();
		cameraEntity.AddComponent<CameraComponent>(camera);

		std::shared_ptr<Texture> texture = ResourceAllocator<Texture>::Get("assets/images/dino.png");

		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture);

		for (int x = -10; x <= 10; x++)
		{
			for (int y = -10; y <= 10; y++)
			{
				Entity entity = CreateEntity();

				auto& spriteComponent = entity.AddComponent<SpriteComponent>();
				spriteComponent.Sprite = sprite;

				auto& transformComponent = entity.GetComponent<TransformComponent>();

				transformComponent.Transform.Position = glm::vec3(x, y, 0.0f);
			}
		}

		sceneSystems.push_back(new CameraControllerSystem(registry));
		sceneSystems.push_back(new SpriteRenderSystem(registry));

		for (auto system : sceneSystems)
		{
			system->Start();
		}

		Renderer2D::Initialize();
	}

	void SandboxScene::Update(float deltaTime)
	{
		RenderCommand::Clear();
		Scene::Update(deltaTime);

		Renderer2D::BeginScene(camera);

		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				Renderer2D::DrawQuad({ .Position = { i - 5, j - 5, 0.0f }, .Texture = texture, .Color = { 0.4f, 1.0f, 1.0f, 0.7f }, .Tiling = 3.0f });
			}

		}

		Renderer2D::EndScene();
	}
}