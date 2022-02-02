#include "RenderCommand.h"

namespace Alpha
{
	std::unique_ptr<RendererAPI> RenderCommand::RendererApi;

	void RenderCommand::Initialize()
	{
		RendererApi->Initialize();
	}

	void RenderCommand::SetAPI(API api)
	{
		RendererAPI::Api = api;
		RendererApi.reset(RendererAPI::Create());
	}

	void RenderCommand::DrawIndexed(const VertexArray& vertexArray)
	{
		RendererApi->DrawIndexed(vertexArray);
	}

	void RenderCommand::DrawIndexed(const VertexArray& vertexArray, size_t amount)
	{
		RendererApi->DrawIndexed(vertexArray, amount);
	}

	void RenderCommand::SetClearColor(const glm::vec4& color)
	{
		RendererApi->SetClearColor(color);
	}

	void RenderCommand::Clear()
	{
		RendererApi->Clear();
	}
}