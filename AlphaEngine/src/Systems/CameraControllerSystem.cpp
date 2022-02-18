#include "CameraControllerSystem.h"

#include "Controls/Input.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

#include "Events/WindowResizedEvent.h"

namespace Alpha
{
	CameraControllerSystem::CameraControllerSystem(entt::registry& registry) : System(registry)
	{
		movementSpeed = 10.0f;
		scrollSpeed = 10.0f;
	}

	void CameraControllerSystem::Update(float deltaTime)
	{
		auto view = registry.view<TransformComponent, CameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			if (Alpha::Input::IsKeyDown(GLFW_KEY_W))
			{
				transform.Transform.Position.y += movementSpeed * deltaTime;
			}
			else if (Alpha::Input::IsKeyDown(GLFW_KEY_S))
			{
				transform.Transform.Position.y -= movementSpeed * deltaTime;
			}

			if (Alpha::Input::IsKeyDown(GLFW_KEY_D))
			{
				transform.Transform.Position.x += movementSpeed * deltaTime;
			}
			else if (Alpha::Input::IsKeyDown(GLFW_KEY_A))
			{
				transform.Transform.Position.x -= movementSpeed * deltaTime;
			}

			if (Input::HasScroll())
			{
				float scrolledZoom = camera.Camera.GetZoom();
				scrolledZoom -= scrollSpeed * Input::GetScroll().y * deltaTime;

				camera.Camera.SetZoom(scrolledZoom);
			}
		}
	}

	void CameraControllerSystem::OnEvent(Event& event)
	{
		Dispatcher::Dispatch<WindowResizedEvent>(event, EVENT_BIND(OnWindowResized));
	}

	bool CameraControllerSystem::OnWindowResized(WindowResizedEvent& event)
	{
		float newAspectRatio = static_cast<float>(event.GetNewSize().x) / event.GetNewSize().y;

		auto view = registry.view<CameraComponent>();

		for (auto& entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);

			camera.Camera.SetAspectRatio(newAspectRatio);
		}

		return false;
	}
}

