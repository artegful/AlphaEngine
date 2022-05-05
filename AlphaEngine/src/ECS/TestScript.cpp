#include "TestScript.h"

#include "Controls/Input.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/OrthoCameraComponent.h"
#include "Components/TransformComponent.h"
#include "box2d/b2_body.h"

namespace Alpha
{
	TestScript::TestScript(const Entity& entity, entt::registry& registry) : Script(entity, registry)
	{ }

	void TestScript::Start()
	{

	}

	void TestScript::Update(float deltaTime)
	{
		UpdateMovement(deltaTime);
		UpdateJumping(deltaTime);

		UpdateCameraFollower();
	}

	void TestScript::Jump(float force)
	{
		auto& rigid = GetComponent<Rigidbody2DComponent>();
		rigid.AddForce({ 0, 1 }, force);
		isInJump = true;
	}

	void TestScript::UpdateJumping(float deltaTime)
	{
		if (isInJump)
		{
			return;
		}

		if (Input::IsKeyDown(GLFW_KEY_SPACE))
		{
			forceMeter += deltaTime * 10;
		}
		else if (forceMeter > 0.1f)
		{
			Jump(std::min(forceMeter * forceMeter, MaxJumpForce));
			forceMeter = 0.0f;
		}
		else
		{
			forceMeter = 0.0f;
		}
	}

	void TestScript::UpdateMovement(float deltaTime)
	{
		auto& rigidbody = GetComponent<Rigidbody2DComponent>();

		float yVelocity = rigidbody.Body->GetLinearVelocity().y;

		if (isInJump && abs(yVelocity) < 0.01f)
		{
			framesWithoutJump++;
			if (framesWithoutJump > 10)
			{
				isInJump = false;
				framesWithoutJump = 0;
			}
		}

		if (!isInJump)
		{
			return;
		}

		float forceMultiplier = yVelocity > 0 ? yVelocity : previousForceMultiplier + yVelocity;
		forceMultiplier = std::max(0.0f, forceMultiplier);

		previousForceMultiplier = forceMultiplier;

		if (Input::IsKeyDown(GLFW_KEY_D))
		{
			rigidbody.AddForce({ 1.0f, 0.0f }, forceMultiplier * deltaTime);
		}
		else if (Input::IsKeyDown(GLFW_KEY_A))
		{
			rigidbody.AddForce({ -1.0f, 0.0f }, forceMultiplier * deltaTime);
		}
	}

	void TestScript::UpdateCameraFollower()
	{
		auto view = registry.view<OrthoCameraComponent>();

		for (auto e : view)
		{
			auto& transform = registry.get<TransformComponent>(e);
			transform.Transform.Position.y = GetComponent<TransformComponent>().Transform.Position.y;
		}
	}
}