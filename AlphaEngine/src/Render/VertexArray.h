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
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& buffer) = 0;

		virtual std::size_t GetAmountOfElements() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};
}