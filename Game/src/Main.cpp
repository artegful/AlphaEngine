#include "Core/Config.h"
#include "Core/Engine.h"
#include "Layers/GameLayer.h"

int main()
{
	Alpha::Engine engine({ 1920, 1080, Alpha::API::OpenGL });

	engine.GetLayerStack().AddLayer(new Alpha::GameLayer());

	engine.Run();

	return 0;
}