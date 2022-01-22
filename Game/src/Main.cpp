#include "Core/Config.h"
#include "Core/Engine.h"
#include "Layers/GameLayer.h"
#include "Layers/DebugLayer.h"

int main()
{
	Alpha::Engine engine({ 1920, 1080, Alpha::API::OpenGL });

	engine.GetLayerStack().AddLayer(new Alpha::GameLayer());
	engine.GetLayerStack().AddLayer(new Alpha::DebugLayer());
	engine.Run();

	return 0;
}