#pragma once

#include <memory>

namespace Alpha
{
	class VertexBuffer;
	class IndexBuffer;

	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& buffer) = 0;
		virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;
	};
}