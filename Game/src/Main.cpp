#include "Core/Config.h"
#include "Core/Engine.h"

int main()
{
	Alpha::Engine engine({ 1920, 1080, Alpha::API::OpenGL });

	engine.Run();

	return 0;
}