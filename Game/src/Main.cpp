#include "Core/Config.h"
#include "Core/Engine.h"
#include "Layers/GameLayer.h"
#include "Layers/DebugLayer.h"

int main()
{
	Alpha::Engine engine(Alpha::Config{ 1920, 1080, Alpha::API::OpenGL, Alpha::GameMode::Game,  false });
	engine.Initialize();

	//engine.GetGameLayer().GetSceneManager().ChangeScene("assets/scenes/90001.scene");
	//engine.GetLayerStack().AddOverlay(new Alpha::DebugLayer());

	engine.Run();

	return 0;
}