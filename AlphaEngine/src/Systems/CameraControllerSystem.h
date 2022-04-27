#pragma once

#include "ECS/System.h"

namespace Alpha
{
	struct WindowResizedEvent;
	class ProjectionCamera;
	struct Transform;

	class CameraControllerSystem : public System
	{
	public:
		CameraControllerSystem(SceneManager* sceneManager);

		void Update(float deltaTime) override;
		void OnEvent(Event& event) override;

		void UpdateCamera(float deltaTime, Transform& cameraTransform, ProjectionCamera& camera);
		void UpdateTransformPosition(float deltaTime, Transform& transform);
		void UpdateCameraZoom(float deltaTime, ProjectionCamera& camera);

	private:
		float scrollSpeed;
		float movementSpeed;

		bool OnWindowResized(WindowResizedEvent& event);
	};
}
