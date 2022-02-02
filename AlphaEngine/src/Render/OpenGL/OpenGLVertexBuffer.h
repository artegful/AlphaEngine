#pragma once

#include "GL/glew.h"
#include "Render/VertexBuffer.h"

namespace Alpha
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(void* buffer, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);

		~OpenGLVertexBuffer();

		void Bind() override;
		void Unbind() override;

		void SetLayout(const std::shared_ptr<BufferLayout>& bufferLayout) override;
		const BufferLayout& GetLayout() const override;

		void SetData(void* data, size_t size) override;

	private:
		OpenGLVertexBuffer();

		GLuint id;
		std::shared_ptr<BufferLayout> bufferLayout;
	};
}

