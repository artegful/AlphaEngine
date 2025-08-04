#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Engine.h"
#include "Core/Config.h"
#include "Scene/Scene.h"
#include <Systems/CameraControllerSystem.h>
#include <Systems/RenderSystem.h>
#include <Systems/ScriptSystem.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(SystemsTests)
	{
	public:
		TEST_METHOD(CameraSystemsInitializes)
		{
			Alpha::CameraControllerSystem system(new Alpha::SceneManager());

			Assert::IsTrue(true);
		}

		TEST_METHOD(RenderSystemInitializes)
		{
			Alpha::RenderSystem system(new Alpha::SceneManager());

			Assert::IsTrue(true);
		}

		TEST_METHOD(ScriptSystemInitializes)
		{
			Alpha::ScriptSystem system(new Alpha::Scene());

			Assert::IsTrue(true);
		}
	};
}
