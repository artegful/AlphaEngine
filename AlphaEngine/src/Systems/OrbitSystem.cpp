#include "OrbitSystem.h"

#include "entt/entt.hpp"
#include "ECS/Entity.h"
#include <Components/SpriteComponent.h>
#include <Components/BenchmarkComponent.h>
#include <Components/ModelComponent.h>
#include <Components/PerspectiveCameraComponent.h>
#include <Components/TransformComponent.h>
#include <Components/PointLightComponent.h>
#include <random>

namespace Alpha
{

	OrbitSystem::OrbitSystem(Scene* scene) : SceneSystem(scene)
	{

	}

	void OrbitSystem::Open()
	{

	}

	void OrbitSystem::Start()
	{
		std::srand(std::time(nullptr));
		constexpr int size = 25000;
		constexpr float randomRange = 150;
		constexpr float radius = 450;

		std::random_device rd{};
		std::mt19937 gen{ rd() };

		std::normal_distribution<> d{ 0, 60 };

		for (int i = 0; i < size; i++)
		{
			Entity entity = scene->CreateEntity();
			auto& benchmark = entity.AddComponent<BenchmarkComponent>();
			benchmark.Speed = static_cast<float>(std::rand()) / RAND_MAX * 40 - 20;

			if (benchmark.Speed > 0.0f)
			{
				benchmark.Speed = std::max(benchmark.Speed, 8.0f);
			}
			else
			{
				benchmark.Speed = std::min(benchmark.Speed, -8.0f);
			}

			auto& component = entity.AddComponent<ModelComponent>();
			component.SetPath("assets/models/rock/rock.obj");

			auto& transform = entity.GetComponent<TransformComponent>();

			float angle = (float)i / (float)size * 360.0f;
			transform.Transform.Position.x = sin(angle) * radius + d(gen);
			transform.Transform.Position.y = d(gen) * 0.7f;
			transform.Transform.Position.z = cos(angle) * radius + d(gen);

			transform.Transform.Scale = glm::vec3(1);

			transform.Transform.Rotation = { GetRandom(360), GetRandom(360), GetRandom(360) };
			benchmark.Speed = 0.02 + GetRandom(0.015);
		}

		Entity planetEntity = scene->CreateEntity("planet");
		auto& planetModel = planetEntity.AddComponent<ModelComponent>();
		planetModel.SetPath("assets/models/planet/planet.obj");

		auto& planetTransform = planetEntity.GetComponent<TransformComponent>();
		planetTransform.Transform.Scale = glm::vec3(20);

		Entity sunEntity = scene->CreateEntity("Sun");
		auto& sunModel = sunEntity.AddComponent<ModelComponent>();
		sunModel.SetPath("assets/models/sun/sun.obj");

		auto& light = sunEntity.AddComponent<PointLightComponent>().Light;
		light.Color = { 0.6f, 0.2f, 0.0f, 1.0f };
		light.ConstantFalloff = 0.0000000001f;
		light.LinearFalloff = 0.000000001f;
		light.QuadraticFalloff = 0.0000002f;
		light.Ambient = glm::vec3(0.1);

		auto& sunTransform = sunEntity.GetComponent<TransformComponent>();
		sunTransform.Transform.Scale = glm::vec3(100);
		sunTransform.Transform.Position.x = 100;
		sunTransform.Transform.Position.z = -1500;
	}

	void OrbitSystem::Update(float deltaTime)
	{
		auto view = GetRegistry().view<TransformComponent, BenchmarkComponent>();

		for (auto& entity : view)
		{
			auto [transform, benchmark] = view.get<TransformComponent, BenchmarkComponent>(entity);

			float rotation = benchmark.Speed * deltaTime;
			float cos = std::cos(rotation);
			float sin = std::sin(rotation);

			float x = cos * transform.Transform.Position.x - sin * transform.Transform.Position.z;
			float z = sin * transform.Transform.Position.x + cos * transform.Transform.Position.z;

			transform.Transform.Position.x = x;
			transform.Transform.Position.z = z;
		}
	}

	float OrbitSystem::GetRandom(float range)
	{
		return (static_cast<float>(std::rand()) / RAND_MAX - 0.5f) * range;
	}
}
