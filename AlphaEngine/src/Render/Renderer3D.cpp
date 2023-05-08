#include "Renderer3D.h"

#include "Resources/ResourceAllocator.hpp"

namespace Alpha
{
	std::shared_ptr<Shader> Renderer3D::modelShader;

	void Renderer3D::Initialize()
	{
		modelShader = ResourceAllocator<Shader>::Get("assets/shaders/model.glsl");
	}

	void Renderer3D::BeginScene(const RenderCamera& camera)
	{
		modelShader->Bind();
		modelShader->SetMat4("uViewProjectionMatrix", camera.GetViewProjectionMatrix());
	}

	void Renderer3D::DrawModel(Model& model, const Transform& transform)
	{
		modelShader->SetMat4("model", transform.GetTransformMatrix());

		model.Draw(*modelShader);
	}

	void Renderer3D::EndScene() 
	{
		modelShader->Unbind();
	}
}

