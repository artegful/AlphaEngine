#pragma once

#include <stdint.h>
#include <memory>

#include "Core/Core.h"
#include "RendererAPI.h"

namespace Alpha
{
	class BufferLayout;

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetLayout(const std::shared_ptr<BufferLayout>& layout) = 0;
		virtual const BufferLayout& GetLayout() const = 0;

		static VertexBuffer* Create(const float* buffer, uint32_t size);
	};
}
