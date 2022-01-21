#include "VertexBuffer.h"

#include "Render/OpenGL/OpenGLVertexBuffer.h"

namespace Alpha
{
	VertexBuffer* VertexBuffer::Create(const float* buffer, uint32_t size)
	{
		switch (RendererAPI::GetAPI())
		{
			case API::OpenGL: return new OpenGLVertexBuffer(buffer, size);
		}

		AL_ENGINE_ASSERT(false, "Selected Rendering API is not supported");
		return nullptr;
	}
}