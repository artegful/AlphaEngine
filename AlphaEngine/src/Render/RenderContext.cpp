#include "RenderContext.h"

#include "Core/Core.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLRenderContext.h"

namespace Alpha
{
	RenderContext* RenderContext::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case API::OpenGL: return new OpenGLRenderContext();
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}
}