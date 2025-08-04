#include "BenchmarkSystem.h"

#include "entt/entt.hpp"
#include "ECS/Entity.h"
#include <Components/SpriteComponent.h>
#include <Components/BenchmarkComponent.h>
#include <Components/ModelComponent.h>
#include <Components/PerspectiveCameraComponent.h>
#include <Components/TransformComponent.h>

namespace Alpha
{
	BenchmarkSystem::BenchmarkSystem(Scene * scene) : SceneSystem(scene)
	{

	}

	void BenchmarkSystem::Start()
	{
		std::srand(std::time(nullptr));
		glm::vec2 uvs[4]{ { 0, 0 }, {0.2f, 0}, {0.2f, 0.3f}, {0, 0.3f} };
		constexpr int size = 356;
		for (int i = -size / 2; i < size / 2; i++)
		{
			for (int j = -size / 2; j < size / 2; j++)
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

				if (j % 2 == 0)
				{
					auto& component = entity.AddComponent<ModelComponent>();
					component.SetPath("assets/models/defaultCube/cube.obj");

				}
				else
				{
					auto& component = entity.AddComponent<SpriteComponent>();
					component.SetPath("assets/images/bee.png");
				}

				auto& transform = entity.GetComponent<TransformComponent>();
				transform.Transform.Position = { i, j * static_cast<float>(std::rand()) / RAND_MAX * 5 - 2.5f, 0 };
				transform.Transform.Scale.x = benchmark.Speed < 0.0f ? 1.0f : -1.0f;
			}
		}
	}

	void BenchmarkSystem::Update(float deltaTime)
	{
		auto view = GetRegistry().view<TransformComponent, BenchmarkComponent>();

		for (auto& entity : view)
		{
			auto [transform, benchmark] = view.get<TransformComponent, BenchmarkComponent>(entity);

			if (benchmark.Speed > 0 && transform.Transform.Position.x > 200 || benchmark.Speed < 0 && transform.Transform.Position.x < -200)
			{
				benchmark.Speed = -benchmark.Speed;
				transform.Transform.Scale.x = -transform.Transform.Scale.x;
			}

			transform.Transform.Position.x += benchmark.Speed * deltaTime;
		}
	}
}
