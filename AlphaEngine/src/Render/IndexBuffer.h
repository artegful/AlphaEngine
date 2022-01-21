#pragma once

namespace Alpha
{
	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual uint32_t GetAmountOfElements() const = 0;
	};
}
