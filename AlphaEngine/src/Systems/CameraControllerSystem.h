#pragma once

#include "ECS/System.h"
#include "glm/vec3.hpp"

namespace Alpha
{
	struct WindowResizedEvent;
	class PerspectiveCamera;
	struct Transform;

	class CameraControllerSystem : public System
	{
	public:
		CameraControllerSystem(SceneManager* sceneManager);

		void Update(float deltaTime) override;
		void OnEvent(Event& event) override;

		void UpdateCamera(float deltaTime, Transform& cameraTransform, PerspectiveCamera& camera);
		void UpdateTransformPosition(float deltaTime, Transform& transform);
		void UpdateCameraZoom(float deltaTime, PerspectiveCamera& camera);
		void UpdateCameraRotation(float deltaTime, Transform& transform);
		void UpdateTransformPositionWhenRightKeyIsHeld(float deltaTime, Transform& transform);

	private:
		float scrollSpeed;
		float movementSpeed;
		float lookAroundSpeed;

		bool OnWindowResized(WindowResizedEvent& event);
		glm::vec3 GetLocalTranslation(const glm::vec3& translation, const Transform& transform);
	};
}
