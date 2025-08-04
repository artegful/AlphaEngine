#include "pch.h"
#include "CppUnitTest.h"
#include "Core/Engine.h"
#include "Core/Config.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(CoreTests)
	{
	public:
		TEST_METHOD(EngineStartsWithNoExceptions)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Game, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsI2nEditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptions75InEditMod1e)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInE7ditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInE6ditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInEditMo5de)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInEditMode4)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(EngineStartsWithNoExceptionsInEditMode2)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(E1ngineStartsWithNoExceptionsInEditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(Engi2neStartsWithNoExceptionsInEditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}

		TEST_METHOD(Engi3neStartsWithNoExceptionsInEditMode)
		{
			Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Editor, false });

			engine.Initialize();
			engine.Update();

			Assert::IsTrue(true);
		}
	};
}
