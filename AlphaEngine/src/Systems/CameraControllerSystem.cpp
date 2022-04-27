#include "CameraControllerSystem.h"

#include "Controls/Input.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"

#include "Events/WindowResizedEvent.h"

namespace Alpha
{
	CameraControllerSystem::CameraControllerSystem(SceneManager* sceneManager) : System(sceneManager)
	{
		movementSpeed = 10.0f;
		scrollSpeed = 10.0f;
	}

	void CameraControllerSystem::Update(float deltaTime)
	{
		auto view = GetRegistry().view<TransformComponent, CameraComponent>();

		for (auto& entity : view)
		{
			auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);

			UpdateCamera(deltaTime, transform.Transform, camera.Camera);
		}
	}

	void CameraControllerSystem::OnEvent(Event& event)
	{
		Dispatcher::Dispatch<WindowResizedEvent>(event, EVENT_BIND(OnWindowResized));
	}

	void CameraControllerSystem::UpdateCamera(float deltaTime, Transform& cameraTransform, ProjectionCamera& camera)
	{
		UpdateTransformPosition(deltaTime, cameraTransform);
		UpdateCameraZoom(deltaTime, camera);
	}

	void CameraControllerSystem::UpdateTransformPosition(float deltaTime, Transform& transform)
	{
		if (Alpha::Input::IsKeyDown(GLFW_KEY_W))
		{
			transform.Position.y += movementSpeed * deltaTime;
		}
		else if (Alpha::Input::IsKeyDown(GLFW_KEY_S))
		{
			transform.Position.y -= movementSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyDown(GLFW_KEY_D))
		{
			transform.Position.x += movementSpeed * deltaTime;
		}
		else if (Alpha::Input::IsKeyDown(GLFW_KEY_A))
		{
			transform.Position.x -= movementSpeed * deltaTime;
		}
	}

	void CameraControllerSystem::UpdateCameraZoom(float deltaTime, ProjectionCamera& camera)
	{
		if (Input::HasScroll())
		{
			float scrolledZoom = camera.GetZoom();
			scrolledZoom -= scrollSpeed * Input::GetScroll().y * deltaTime;

			camera.SetZoom(scrolledZoom);
		}
	}

	bool CameraControllerSystem::OnWindowResized(WindowResizedEvent& event)
	{
		float newAspectRatio = static_cast<float>(event.GetNewSize().x) / event.GetNewSize().y;

		auto view = GetRegistry().view<CameraComponent>();

		for (auto& entity : view)
		{
			auto& camera = view.get<CameraComponent>(entity);

			camera.Camera.SetAspectRatio(newAspectRatio);
		}

		return false;
	}
}

