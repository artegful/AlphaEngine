#include "System.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

namespace Alpha
{
	System::System(SceneManager* sceneManager) :
		sceneManager(sceneManager)
	{ }

	entt::registry& System::GetRegistry() const
	{
		return sceneManager->GetCurrentScene()->registry;
	}
}

