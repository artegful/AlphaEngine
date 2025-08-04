#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Engine.h"
#include "Core/Config.h"
#include "Scene/Scene.h"
#include "ECS/Entity.h"
#include "Scene/SceneSerializer.h"
#include <Components/SpriteComponent.h>
#include <Components/NameComponent.h>
#include <Components/TransformComponent.h>
#include <Components/ModelComponent.h>
#include <Components/ModelComponent.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(SerializationTests)
	{
	public:
		TEST_METHOD(SceneSerializerGetsAllEntities)
		{
			Alpha::Scene* scene = new Alpha::Scene();
			Alpha::SceneSerializer serializer(scene);

			serializer.Deserialize("assets/scenes/test.scene");
			
			Assert::AreEqual(scene->GetAllEntities().size(), static_cast<size_t>(2));
		}

		TEST_METHOD(SceneSerializerCorrectlyDeserializesTransform)
		{
			Alpha::Scene* scene = new Alpha::Scene();
			Alpha::SceneSerializer serializer(scene);

			serializer.Deserialize("assets/scenes/test.scene");

			Assert::IsTrue(scene->GetAllEntities()[0].HasComponent<Alpha::TransformComponent>());
		}

		TEST_METHOD(SceneSerializerCorrectlyDeserializesName)
		{
			Alpha::Scene* scene = new Alpha::Scene();
			Alpha::SceneSerializer serializer(scene);

			serializer.Deserialize("assets/scenes/test.scene");

			Assert::IsTrue(scene->GetAllEntities()[0].HasComponent<Alpha::NameComponent>());
		}
	};
}
