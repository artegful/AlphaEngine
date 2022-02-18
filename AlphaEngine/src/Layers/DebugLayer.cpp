#include "DebugLayer.h"

#include "imgui.h"
#include "Core/Core.h"
#include "Render/Renderer2D.h"


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

		const Renderer2D::StatsData& stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.Quads);
		ImGui::Text("Vertices: %d", 4 * stats.Quads);
		ImGui::Text("Indices: %d", 6 * stats.Quads);
		ImGui::End();
	}
}