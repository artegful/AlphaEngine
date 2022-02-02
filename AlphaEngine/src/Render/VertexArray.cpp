#include "VertexArray.h"

#include "Core/Core.h"
#include "RendererAPI.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Alpha 
{
	std::shared_ptr<VertexArray> VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}
}

