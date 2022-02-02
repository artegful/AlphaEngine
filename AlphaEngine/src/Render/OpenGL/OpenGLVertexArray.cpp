#include "OpenGLVertexArray.h"

#include "Render/VertexBuffer.h"
#include "Render/IndexBuffer.h"
#include "Render/BufferLayout.h"

namespace Alpha
{
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &id);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(id);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer)
	{
		glBindVertexArray(id);

		buffer->Bind();
		const BufferLayout& layout = buffer->GetLayout();

		int index = 0;
		for (const auto& element : layout)
		{
			glVertexAttribPointer(index, element.ElementCount, GetOpenGLType(element.Type), element.IsNormalized, layout.GetStride(), (const void*) element.Offset);
			glEnableVertexAttribArray(index);
			index++;
		}

		buffer->Unbind();
		glBindVertexArray(0);

		//TODO can fail
		vertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer)
	{
		glBindVertexArray(id);
		buffer->Bind();

		glBindVertexArray(0);
		buffer->Unbind();

		indexBuffer = buffer;
	}

	std::size_t OpenGLVertexArray::GetAmountOfElements() const
	{
		return indexBuffer->GetAmountOfElements();
	}
}