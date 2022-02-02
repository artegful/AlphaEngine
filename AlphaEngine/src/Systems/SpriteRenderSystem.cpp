#include "SpriteRenderSystem.h"

#include "Render/Sprite.h"
#include "Render/RenderCommand.h"

#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"

namespace Alpha
{
	SpriteRenderSystem::SpriteRenderSystem(entt::registry& registry) : System(registry)
	{
	}

	void SpriteRenderSystem::Start()
	{
		if (spriteBatches.empty())
		{
			spriteBatches.emplace_back();
		}

		auto view = registry.view<TransformComponent, SpriteComponent>();

		for (auto& entity : view)
		{
			auto [transform, sprite] = view.get<TransformComponent, SpriteComponent>(entity);

			AddToNearestBatch(transform, sprite);
		}
	}

	void SpriteRenderSystem::Update(float deltaTime)
	{
		auto view = registry.view<TransformComponent, CameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			for (auto& spriteBatch : spriteBatches)
			{
				spriteBatch.Draw(camera, transform);
			}

			break;
		}
	}

	void SpriteRenderSystem::AddToNearestBatch(const TransformComponent& transform, const SpriteComponent& spriteComponent)
	{
		auto result = std::find_if(spriteBatches.begin(), spriteBatches.end(), [&](const SpriteBatch batch)
			{
				return batch.HasSpace() && (!spriteComponent.Sprite || spriteComponent.Sprite && 
					(batch.HasTexture(spriteComponent.Sprite->GetTexture()) || batch.HasTextureSpace()));
			});

		if (result != spriteBatches.end())
		{
			(*result).AddSprite(spriteComponent, transform);
		}
		else
		{
			spriteBatches.emplace_back();
			spriteBatches.back().AddSprite(spriteComponent, transform);
		}
	}
}

