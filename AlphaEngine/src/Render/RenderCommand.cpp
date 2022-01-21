#include "RenderCommand.h"

namespace Alpha
{
	std::unique_ptr<RendererAPI> RenderCommand::RendererApi;

	void RenderCommand::SetAPI(API api)
	{
		RendererAPI::Api = api;
		RendererApi.reset(RendererAPI::Create());
	}

	void RenderCommand::DrawIndexed()
	{
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