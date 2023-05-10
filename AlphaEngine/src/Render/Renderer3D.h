#pragma once

#include "Model.h"
#include "Light.h"
#include "Shader.h"
#include "Skybox.h"
#include "RenderCamera.h"

namespace Alpha
{
	static class Renderer3D
	{
	public:
		static void Initialize();

		static void BeginScene(const RenderCamera& camera);
		static void BindPointLight(const Transform& transform, const Light& light);
		static void FinishBindingPointLights();
		static void EndScene();
		static void DrawSkybox(Skybox& skybox, const RenderCamera& camera);
		static void DrawModel(Model& model, const Transform& transform);

	private:
		static std::shared_ptr<Shader> modelShader;
		static std::shared_ptr<Shader> skyboxShader;
		static int pointLightsBound;

		static void BindPointLight(const Light& light, const glm::vec3 position, int slot);
		static void BindLight(const Light& light, const std::string& prefix);
	};
}