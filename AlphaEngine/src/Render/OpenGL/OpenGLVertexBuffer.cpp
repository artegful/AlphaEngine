#include "OpenGLVertexBuffer.h"

#include "Core/Core.h"

namespace Alpha
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(void* buffer, uint32_t size) : OpenGLVertexBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, size, buffer, GL_STATIC_DRAW);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size) : OpenGLVertexBuffer()
	{
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
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

	void OpenGLVertexBuffer::SetData(void* data, size_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}
}