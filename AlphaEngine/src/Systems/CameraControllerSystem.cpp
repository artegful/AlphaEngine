#include "CameraControllerSystem.h"

#include "entt/entt.hpp"

#include "Controls/Input.h"
#include "Components/TransformComponent.h"
#include "Components/PerspectiveCameraComponent.h"
#include "Render/PerspectiveCamera.h"

#include "Events/WindowResizedEvent.h"

namespace Alpha
{
	CameraControllerSystem::CameraControllerSystem(SceneManager* sceneManager) : System(sceneManager)
	{
		movementSpeed = 10.0f;
		scrollSpeed = 10.0f;
		lookAroundSpeed = 15.0f;
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
		if (Input::IsMouseButtonDown(1))
		{
			UpdateTransformPositionWhenRightKeyIsHeld(deltaTime, cameraTransform);
		}
		else
		{
			UpdateTransformPosition(deltaTime, cameraTransform);
		}


		UpdateCameraZoom(deltaTime, camera);
		UpdateCameraRotation(deltaTime, cameraTransform);
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

	void CameraControllerSystem::UpdateCameraRotation(float deltaTime, Transform& transform)
	{
		if (!Input::IsMouseButtonDown(1))
		{
			return;
		}

		glm::vec2 mouseDelta = Input::GetMouseDelta();
		transform.Rotation.y -= deltaTime * mouseDelta.x * lookAroundSpeed;
		transform.Rotation.x -= deltaTime * mouseDelta.y * lookAroundSpeed;

		transform.Rotation.x = glm::clamp(transform.Rotation.x, -90.0f, 90.0f);

	}

	void CameraControllerSystem::UpdateTransformPositionWhenRightKeyIsHeld(float deltaTime, Transform& transform)
	{
		glm::mat4 rotationMatrix = glm::toMat4(glm::quat(transform.Rotation));

		if (Alpha::Input::IsKeyDown(GLFW_KEY_W))
		{
			transform.Position += GetLocalTranslation(glm::vec3(0.0f, 0.0f, -1.0f), transform) * movementSpeed * deltaTime;
		}
		else if (Alpha::Input::IsKeyDown(GLFW_KEY_S))
		{
			transform.Position += GetLocalTranslation(glm::vec3(0.0f, 0.0f, 1.0f), transform) * movementSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyDown(GLFW_KEY_D))
		{
			transform.Position += GetLocalTranslation(glm::vec3(1.0f, 0.0f, 0.0f), transform) * movementSpeed * deltaTime;
		}
		else if (Alpha::Input::IsKeyDown(GLFW_KEY_A))
		{
			transform.Position += GetLocalTranslation(glm::vec3(-1.0f, 0.0f, 0.0f), transform) * movementSpeed * deltaTime;
		}

		if (Alpha::Input::IsKeyDown(GLFW_KEY_E))
		{
			transform.Position += GetLocalTranslation(glm::vec3(0.0f, 1.0f, 0.0f), transform) * movementSpeed * deltaTime;
		}
		else if (Alpha::Input::IsKeyDown(GLFW_KEY_Q))
		{
			transform.Position += GetLocalTranslation(glm::vec3(0.0f, -1.0f, 0.0f), transform) * movementSpeed * deltaTime;
		}

	}

	bool CameraControllerSystem::OnWindowResized(WindowResizedEvent& event)
	{
		float newAspectRatio = static_cast<float>(event.GetNewSize().x) / event.GetNewSize().y;

		auto view = GetRegistry().view<PerspectiveCameraComponent>();

		for (auto& entity : view)
		{
			auto& camera = view.get<PerspectiveCameraComponent>(entity);

			camera.Camera.SetAspectRatio(newAspectRatio);
		}

		return false;
	}

	glm::vec3 CameraControllerSystem::GetLocalTranslation(const glm::vec3& translation, const Transform& transform)
	{
		glm::vec4 rotatedVector = transform.GetTransformMatrix() * glm::vec4(translation, 0.0f);
		
		return glm::normalize(glm::vec3(rotatedVector));
	}
}

