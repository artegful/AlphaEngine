#pragma once

#include "ECS/System.h"

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

	private:
		float scrollSpeed;
		float movementSpeed;

		bool OnWindowResized(WindowResizedEvent& event);
	};
}
