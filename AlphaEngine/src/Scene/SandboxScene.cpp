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
	void SandboxScene::Open()
	{
		for (auto system : sceneSystems)
		{
			system->Start();
		}
	}

	void SandboxScene::Update(float deltaTime)
	{
		Renderer2D::ResetStats();

		RenderCommand::Clear();
		Scene::Update(deltaTime);
	}
}