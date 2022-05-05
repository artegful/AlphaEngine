#include "Rigidbody2DComponent.h"

#include "box2d/b2_body.h"

namespace Alpha
{
	void Rigidbody2DComponent::AddForce(glm::vec2 direction, float force)
	{
		glm::vec2 forceVector = force * direction;
		Body->ApplyLinearImpulseToCenter({ forceVector.x, forceVector.y }, true);
	}
}