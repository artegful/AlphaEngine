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

		void Bind();
		void Unbind();

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer);
		void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer);

	private:
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers;
		std::shared_ptr<IndexBuffer> indexBuffer;
		GLuint id;
	};
}
