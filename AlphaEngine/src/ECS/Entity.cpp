#include "Entity.h"

namespace Alpha
{
	Entity::Entity(Alpha::Scene* scene, entt::entity handle) :
		scene(scene), handle(handle)
	{ }
}

