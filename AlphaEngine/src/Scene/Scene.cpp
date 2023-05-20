#include "Scene.h"

#include "box2d/b2_world.h"
#include "box2d/b2_body.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_fixture.h"
#include "ECS/Entity.h"
#include "ECS/SceneSystem.h"
#include "Components/NameComponent.h"
#include "Components/TransformComponent.h"
#include "Events/Event.h"
#include "Core/Engine.h"
#include "Render/ProjectionCamera.h"
#include "Render/RenderCamera.h"
#include "Components/PerspectiveCameraComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Box2DColliderComponent.h"
#include "Systems/ScriptSystem.h"
#include "Components/NativeScriptComponent.h"
#include "ECS/TestScript.h"
#include "Core/Window.h"
#include "Controls/Input.h"
#include "Render/Renderer3D.h"

namespace Alpha
{
	b2BodyType EditorPhysicsBodyTypeToBox2D(Rigidbody2DComponent::BodyType type)
	{
		switch (type)
		{
		case Rigidbody2DComponent::BodyType::Static: return b2BodyType::b2_staticBody;
		case Rigidbody2DComponent::BodyType::Dynamic: return b2BodyType::b2_dynamicBody;
		case Rigidbody2DComponent::BodyType::Kinematic: return b2BodyType::b2_kinematicBody;
		}
	}

	Scene::Scene() :
		registry{},
		sceneSystems{ new ScriptSystem(this) }
	{ 

	}

	void Scene::Open()
	{
		if (!skyboxPath.empty())
		{
			Renderer3D::SetSkybox(skyboxPath);
		}
		else
		{
			Renderer3D::SetDefaultSkybox();
		}
	}

	void Scene::Start()
	{
		physicsWorld = new b2World({ 0.0f, -9.81f });

		auto view = registry.view<Rigidbody2DComponent>();

		for (auto id : view)
		{
			Entity entity{ this, id };

			auto& transform = entity.GetComponent<TransformComponent>();
			auto& rigidbodyComponent = entity.GetComponent<Rigidbody2DComponent>();

			b2BodyDef bodyDef;
			bodyDef.type = EditorPhysicsBodyTypeToBox2D(rigidbodyComponent.Type);

			//remove
			if (rigidbodyComponent.Type == Rigidbody2DComponent::BodyType::Dynamic && !entity.HasComponent<NativeScriptComponent>())
			{
				auto& component = entity.AddComponent<NativeScriptComponent>();
				component.SetScript<TestScript>();
			}

			bodyDef.position.Set(transform.Transform.Position.x, transform.Transform.Position.y);
			bodyDef.angle = glm::radians(transform.Transform.Rotation.z);

			b2Body* body = physicsWorld->CreateBody(&bodyDef);
			body->SetFixedRotation(rigidbodyComponent.IsFixedRotation);
			rigidbodyComponent.Body = body;

			if (entity.HasComponent<Box2DColliderComponent>())
			{
				auto& boxColliderComponent = entity.GetComponent<Box2DColliderComponent>();

				b2PolygonShape boxShape;
				boxShape.SetAsBox(boxColliderComponent.Size.x / 2.0f * transform.Transform.Scale.x, 
					boxColliderComponent.Size.y / 2.0f * transform.Transform.Scale.y);

				b2FixtureDef fixtureDef;
				fixtureDef.shape = &boxShape;
				fixtureDef.density = boxColliderComponent.Density;
				fixtureDef.friction = boxColliderComponent.Friction;
				fixtureDef.restitution = boxColliderComponent.Restitution;
				fixtureDef.restitutionThreshold = boxColliderComponent.RestitutionThreshold;
				body->CreateFixture(&fixtureDef);
			}
		}

		for (auto system : sceneSystems)
		{
			system->Start();
		}
	}

	void Scene::Stop()
	{
		delete physicsWorld;
		physicsWorld = nullptr;
	}

	void Scene::Update(float deltaTime)
	{
		for (auto system : sceneSystems)
		{
			system->Update(deltaTime);
		}

		{
			const int32_t velocityIterations = 6;
			const int32_t positionIterations = 2;
			physicsWorld->Step(deltaTime, velocityIterations, positionIterations);

			auto view = registry.view<Rigidbody2DComponent>();
			for (auto e : view)
			{
				Entity entity = { this, e };
				auto& transform = entity.GetComponent<TransformComponent>();
				auto& rigidbodyComponent = entity.GetComponent<Rigidbody2DComponent>();

				b2Body* body = rigidbodyComponent.Body;
				const auto& position = body->GetPosition();
				transform.Transform.Position.x = position.x;
				transform.Transform.Position.y = position.y;
				transform.Transform.Rotation.z = glm::degrees(body->GetAngle());
			}
		}
	}

	void Scene::OnEvent(Event& event)
	{
		for (auto system : sceneSystems)
		{
			system->OnEvent(event);
		}
	}

	Entity Scene::CreateEntity()
	{
		return CreateEntity("Entity (" + std::to_string(amountOfUnnamedEntities++) + ")");
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		entt::entity handle = registry.create();

		registry.emplace<TransformComponent>(handle);
		registry.emplace<NameComponent>(handle, name);

		return Entity(this, handle);
	}

	void Scene::DestroyEntity(const Entity& entity)
	{
		registry.destroy(entity.handle);
	}

	std::vector<Entity> Scene::GetAllEntities()
	{
		std::vector<Entity> entities;

		registry.each([&](entt::entity handle)
			{
				entities.push_back(Entity(this, handle));
			});

		return entities;
	}
}
