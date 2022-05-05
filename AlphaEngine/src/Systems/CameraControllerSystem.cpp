#include "CameraControllerSystem.h"

#include "entt/entt.hpp"

#include "Controls/Input.h"
#include "Components/TransformComponent.h"
#include "Components/OrthoCameraComponent.h"
#include "Render/PerspectiveCamera.h"

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

	}

	void CameraControllerSystem::OnEvent(Event& event)
	{
		Dispatcher::Dispatch<WindowResizedEvent>(event, EVENT_BIND(OnWindowResized));
	}

	void CameraControllerSystem::UpdateCamera(float deltaTime, Transform& cameraTransform, PerspectiveCamera& camera)
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

	void CameraControllerSystem::UpdateCameraZoom(float deltaTime, PerspectiveCamera& camera)
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

		auto view = GetRegistry().view<OrthoCameraComponent>();

		for (auto& entity : view)
		{
			auto& camera = view.get<OrthoCameraComponent>(entity);

			camera.Camera.SetAspectRatio(newAspectRatio);
		}

		return false;
	}
}

