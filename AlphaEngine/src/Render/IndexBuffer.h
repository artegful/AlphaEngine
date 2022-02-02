#pragma once

#include <memory>
#include <stdint.h>

namespace Alpha
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetAmountOfElements() const = 0;

		static std::shared_ptr<IndexBuffer> Create(const uint32_t* buffer, std::size_t count);
	};
}
