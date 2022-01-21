#include "SandboxScene.h"

#include "ECS/Entity.h"

#include "Render/Texture.h"
#include "Render/Sprite.h"

#include "Resources/ResourceAllocator.hpp"

#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Components/SpriteComponent.h"

#include "Systems/CameraControllerSystem.h"
#include "Systems/SpriteRenderSystem.h"

namespace Alpha
{
	void SandboxScene::Open()
	{
		Entity camera = CreateEntity();
		camera.AddComponent<CameraComponent>(16.0f / 9.0f);

		Texture* texture = new Texture("assets/images/dino.png");

		std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(texture);

		for (int x = -30; x <= 30; x++)
		{
			for (int y = -30; y <= 30; y++)
			{
				Entity entity = CreateEntity();

				auto& spriteComponent = entity.AddComponent<SpriteComponent>();
				spriteComponent.Sprite = sprite;

				auto& transform = entity.GetComponent<TransformComponent>();

				transform.Position = glm::vec3(x, y, 0.0f);
			}
		}

		sceneSystems.push_back(new CameraControllerSystem(registry));
		sceneSystems.push_back(new SpriteRenderSystem(registry));

		for (auto system : sceneSystems)
		{
			system->Start();
		}
	}
}