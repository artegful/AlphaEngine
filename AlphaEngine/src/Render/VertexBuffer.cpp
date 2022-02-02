#include "VertexBuffer.h"

#include "Render/OpenGL/OpenGLVertexBuffer.h"

namespace Alpha
{
	std::shared_ptr<VertexBuffer> VertexBuffer::Create(void* buffer, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(buffer, size);
		}

		AL_ENGINE_ASSERT(false, "Selected Rendering API is not supported");
		return nullptr;
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
		case API::OpenGL: return std::make_shared<OpenGLVertexBuffer>(size);
		}

		AL_ENGINE_ASSERT(false, "Selected Rendering API is not supported");
		return nullptr;
	}
}