#include "CameraControllerSystem.h"

#include "Controls/Input.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

namespace Alpha
{
	void CameraControllerSystem::Update(float deltaTime)
	{
		auto view = registry.view<TransformComponent, CameraComponent>();

		for (auto& entity : view)
		{
			auto& transform = view.get<TransformComponent>(entity);

			if (Alpha::Input::IsKeyDown(GLFW_KEY_W))
			{
				transform.Transform.Position.y += 10.0f * deltaTime;
			}
			else if (Alpha::Input::IsKeyDown(GLFW_KEY_S))
			{
				transform.Transform.Position.y -= 10.0f * deltaTime;
			}

			if (Alpha::Input::IsKeyDown(GLFW_KEY_D))
			{
				transform.Transform.Position.x += 10.0f * deltaTime;
			}
			else if (Alpha::Input::IsKeyDown(GLFW_KEY_A))
			{
				transform.Transform.Position.x -= 10.0f * deltaTime;
			}
		}
	}
}

