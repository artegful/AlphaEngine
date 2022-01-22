#include "DebugLayer.h"

#include "Core/Core.h"

namespace Alpha
{
	void DebugLayer::Update(float deltaTime)
	{
		AL_WARNING("FPS: ", 1.0f / deltaTime);
	}
}