#include "Renderer3D.h"

#include "Core/Core.h"
#include "Resources/ResourceAllocator.hpp"
#include "Components/PointLightComponent.h"
#include "Skybox.h"

namespace Alpha
{
	std::shared_ptr<Shader> Renderer3D::modelShader;
	std::shared_ptr<Shader> Renderer3D::skyboxShader;
	int Renderer3D::pointLightsBound;
	std::shared_ptr<Skybox> Renderer3D::skybox;


	void Renderer3D::Initialize()
	{
		modelShader = ResourceAllocator<Shader>::Get("assets/shaders/model.glsl");
		skyboxShader = ResourceAllocator<Shader>::Get("assets/shaders/skybox.glsl");

		skyboxShader->SetInt("skybox", 0);
	}

	void Renderer3D::BeginScene(const RenderCamera& camera)
	{
		modelShader->Bind();
		modelShader->SetMat4("uViewProjectionMatrix", camera.GetViewProjectionMatrix());
		modelShader->SetFloat3("viewPos", camera.GetTransform().Position);

		modelShader->SetFloat3("dirLight.direction", glm::vec3(0.4f, -1.0f, 0.3f));

		//modelShader->SetFloat3("dirLight.ambient", glm::vec3(0.3f));
		//modelShader->SetFloat3("dirLight.diffuse", glm::vec3(0.7f));
		//modelShader->SetFloat3("dirLight.specular", glm::vec3(0.2f));

		pointLightsBound = 0;
	}

	void Renderer3D::BindPointLight(const Transform& transform, const Light& light)
	{
		BindPointLight(light, transform.Position, pointLightsBound++);
	}

	void Renderer3D::FinishBindingPointLights()
	{
		modelShader->SetInt("pointLightsBound", pointLightsBound);
	}

	void Renderer3D::DrawModel(Model& model, const Transform& transform)
	{
		modelShader->SetMat4("model", transform.GetTransformMatrix());

		model.Draw(*modelShader);
	}

	void Renderer3D::SetSkybox(const std::string& skyboxPath)
	{
		auto textures = std::array<std::string, 6>
		{
				skyboxPath + "/right.jpg",
				skyboxPath + "/left.jpg",
				skyboxPath + "/top.jpg",
				skyboxPath + "/bottom.jpg",
				skyboxPath + "/front.jpg",
				skyboxPath + "/back.jpg"
		};

		skybox = std::make_shared<Skybox>(textures);
	}

	void Renderer3D::SetDefaultSkybox()
	{
		SetSkybox("assets/skyboxes/default");
	}

	void Renderer3D::BindPointLight(const Light& light, const glm::vec3 position, int slot)
	{
		std::string prefix = "pointLights[" + std::to_string(slot) + "].";

		BindLight(light, prefix);

		modelShader->SetFloat3(prefix + "position", position);
	}

	void Renderer3D::BindLight(const Light& light, const std::string& prefix)
	{
		modelShader->SetFloat3(prefix + "color", light.Color);

		modelShader->SetFloat(prefix + "constant", light.ConstantFalloff);
		modelShader->SetFloat(prefix + "linear", light.LinearFalloff);
		modelShader->SetFloat(prefix + "quadratic", light.QuadraticFalloff);

		modelShader->SetFloat3(prefix + "ambient", light.Ambient);
		modelShader->SetFloat3(prefix + "diffuse", light.Diffuse);
		modelShader->SetFloat3(prefix + "specular", light.Specular);
	}

	void Renderer3D::EndScene() 
	{
		modelShader->Unbind();
	}

	void Renderer3D::DrawSkybox(Skybox& skybox, const RenderCamera& camera)
	{
		skyboxShader->Bind();

		skyboxShader->SetMat4("uViewProjectionMatrix", camera.GetViewProjectionMatrixWithoutTranslate());
		skybox.Draw();
	}

	void Renderer3D::DrawSkybox(const RenderCamera& camera)
	{
		AL_ENGINE_ASSERT(skybox.get() != nullptr, "Skybox should be set before drawing it");

		DrawSkybox(*skybox.get(), camera);
	}
}

