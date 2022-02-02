#include "BufferLayout.h"

namespace Alpha
{
	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements) :
		elements(elements)
	{
		ConstructLayout();
	}

	uint32_t BufferLayout::GetStride() const
	{
		return stride;
	}

	std::vector<BufferElement>::const_iterator BufferLayout::begin() const
	{
		const std::vector<int> vector{ 1, 2, 3 };

		std::vector<int>::const_iterator it = vector.begin();

		return elements.begin();
	}

	std::vector<BufferElement>::const_iterator BufferLayout::end() const
	{
		return elements.end();
	}

	void BufferLayout::ConstructLayout()
	{
		stride = 0;
		uint32_t offset = 0;

		for (auto& element : elements)
		{
			element.Offset = offset;

			offset += element.Size;
			stride += element.Size;
		}
	}
}