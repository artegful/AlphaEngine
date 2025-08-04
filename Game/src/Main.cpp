#include "Core/Config.h"
#include "Core/Engine.h"
#include "Layers/GameLayer.h"
#include "Layers/DebugLayer.h"
#include "Scene/Scene.h"
#include <Render/Renderer3D.h>

int main()
{
	Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Game,  false });
	engine.Initialize();

	std::ifstream gameConfigStream("gameConfig.txt");
	if (gameConfigStream.is_open())
	{
		std::stringstream stringStream;
		stringStream << gameConfigStream.rdbuf();
		engine.GetGameLayer().GetSceneManager().ChangeScene(stringStream.str());
	}

	engine.Run();

	return 0;
}