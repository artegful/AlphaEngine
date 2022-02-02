#pragma once

#include <vector>

#include "GL/glew.h"
#include "Render/VertexArray.h"

namespace Alpha
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();

		void Bind() override;
		void Unbind() override;

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) override;

		std::size_t GetAmountOfElements() const override;

	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
		GLuint id;
	};
}
