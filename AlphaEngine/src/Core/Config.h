#pragma once

#include <memory>
#include "Window.h"
#include "Render/API.h"

namespace Alpha
{
	struct Config
	{
		int Width;
		int Height;
		API RenderApi;
		bool IsImGuiEnabled = false;
	};
}


