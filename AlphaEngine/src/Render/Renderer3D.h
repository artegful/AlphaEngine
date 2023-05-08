#pragma once

#include "Model.h"
#include "Shader.h"
#include "RenderCamera.h"

namespace Alpha
{
	static class Renderer3D
	{
	public:
		static void Initialize();

		static void BeginScene(const RenderCamera& camera);
		static void EndScene();
		static void DrawModel(Model& model, const Transform& transform);

	private:
		static std::shared_ptr<Shader> modelShader;
	};
}