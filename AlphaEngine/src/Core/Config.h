#pragma once

#include <memory>
#include "Window.h"
#include "Render/API.h"
#include "Layers/GameMode.h"

namespace Alpha
{
	struct Config
	{
		int Width;
		int Height;
		API RenderApi;
		GameMode Mode;
		bool IsImGuiEnabled = false;
	};
}


