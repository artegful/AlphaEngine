#pragma once

#include "ECS/System.h"

namespace Alpha
{
	struct WindowResizedEvent;

	class CameraControllerSystem : public System
	{
	public:
		CameraControllerSystem(entt::registry& registry);

		void Update(float deltaTime) override;
		void OnEvent(Event& event) override;

	private:
		float scrollSpeed;
		float movementSpeed;

		bool OnWindowResized(WindowResizedEvent& event);
	};
}
