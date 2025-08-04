#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Engine.h"
#include "Core/Config.h"
#include "Core/Layer.h"
#include "Layers/GameLayer.h"
#include "Layers/ImGuiLayer.h"
#include "Layers/DebugLayer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(EngineTests)
	{
	public:
		TEST_METHOD(EngineStartsWithNoExceptions)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Game, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInEditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineHasGameLayer)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(dynamic_cast<Alpha::GameLayer*>(*engine.GetLayerStack().begin()) != nullptr);
		}

		TEST_METHOD(EngineCanDisableImgui)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(dynamic_cast<Alpha::ImGuiLayer*>(*--engine.GetLayerStack().end()) == nullptr);
		}

		TEST_METHOD(EngineCanDisableDebugLayer)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(dynamic_cast<Alpha::DebugLayer*>(*--engine.GetLayerStack().end()) == nullptr);
		}
	};
}
