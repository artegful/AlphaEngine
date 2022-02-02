#include "OpenGLIndexBuffer.h"

namespace Alpha
{
	OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* buffer, std::size_t count) : OpenGLIndexBuffer()
	{
		this->count = count;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(const uint32_t), buffer, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t count) : OpenGLIndexBuffer()
	{
		this->count = count;

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(const uint32_t), NULL, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer() : 
		count(0)
	{
		glGenBuffers(1, &id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &id);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	uint32_t OpenGLIndexBuffer::GetAmountOfElements() const
	{
		return count;
	}
}