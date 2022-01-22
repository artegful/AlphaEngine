#pragma once

#include "Core/Layer.h"

namespace Alpha
{
	class DebugLayer : public Layer
	{
		void Update(float deltaTime) override;
		void OnImGui() override;

	private:
		float framesDeltaTime = 1.0f;
	};
}


