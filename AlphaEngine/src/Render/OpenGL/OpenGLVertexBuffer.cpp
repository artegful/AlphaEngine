#include "OpenGLVertexBuffer.h"

#include "Core/Core.h"

namespace Alpha
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(const float* buffer, uint32_t size) : VertexBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) : VertexBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, size, NULL, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer()
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::SetLayout(const std::shared_ptr<BufferLayout>& bufferLayout)
	{
		this->bufferLayout = bufferLayout;
	}
	const BufferLayout& OpenGLVertexBuffer::GetLayout() const
	{
		AL_ENGINE_ASSERT(bufferLayout, "No buffer layout in vertex buffer");

		return *bufferLayout;
	}
}