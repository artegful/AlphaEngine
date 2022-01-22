#pragma once

#include "Core/Layer.h"

namespace Alpha
{
	class ImGuiLayer : public Layer
	{
	public:
		void Open() override;
		void Close() override;

		static void Begin();
		static void End();
	};
}


