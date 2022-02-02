#include "IndexBuffer.h"

#include "Core/Core.h"
#include "Render/RendererAPI.h"
#include "OpenGL/OpenGLIndexBuffer.h"

namespace Alpha
{
	std::shared_ptr<IndexBuffer> IndexBuffer::Create(const uint32_t* buffer, std::size_t count)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLIndexBuffer>(buffer, count);
		}

		AL_ENGINE_ASSERT(false, "Provided rendering API is not supported");
		return nullptr;
	}
}