#include "DebugLayer.h"

#include "Core/Core.h"

#include "imgui.h"

namespace Alpha
{
	void DebugLayer::Update(float deltaTime)
	{
		framesDeltaTime = deltaTime;
	}

	void DebugLayer::OnImGui()
	{
		ImGui::Begin("Debug window");
		ImGui::Text("%.3f ms (%.1f FPS)", framesDeltaTime * 1000.0f, 1.0f / framesDeltaTime);
		ImGui::End();
	}
}