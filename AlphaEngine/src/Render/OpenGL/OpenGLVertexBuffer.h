#pragma once

#include "GL/glew.h"
#include "Render/VertexBuffer.h"

namespace Alpha
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:

		OpenGLVertexBuffer(const float* buffer, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);

		~OpenGLVertexBuffer();

		void Bind() override;
		void Unbind() override;

		void SetLayout(const std::shared_ptr<BufferLayout>& bufferLayout) override;
		const BufferLayout& GetLayout() const override;

	private:
		OpenGLVertexBuffer();

		GLuint id;
		std::shared_ptr<BufferLayout> bufferLayout;
	};
}

