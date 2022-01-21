#pragma once

#include "Core/Core.h"

#include <format>
#include <string>
#include <vector>
#include <stdint.h>
#include <initializer_list>

#include "GL/glew.h"

namespace Alpha
{
	enum class ElementType
	{
		Int,
		Int2,
		Int3,
		Int4,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Bool
	};

	static int GetSize(ElementType type)
	{
		switch (type)
		{
			case ElementType::Int:    return sizeof(int);
			case ElementType::Int2:   return 2 * sizeof(int);
			case ElementType::Int3:   return 3 * sizeof(int);
			case ElementType::Int4:   return 4 * sizeof(int);
			case ElementType::Float:  return sizeof(float);
			case ElementType::Float2: return 2 * sizeof(float);
			case ElementType::Float3: return 3 * sizeof(float);
			case ElementType::Float4: return 4 * sizeof(float);
			case ElementType::Mat3:	  return 3 * 3 * sizeof(float);
			case ElementType::Mat4:   return 4 * 4 * sizeof(float);
			case ElementType::Bool:   return sizeof(bool);
		}

		AL_ENGINE_ASSERT(false, "The provided element type is not supported");
	}

	static GLenum GetOpenGLType(ElementType type)
	{
		switch (type)
		{
			case ElementType::Int:    return GL_INT;
			case ElementType::Int2:   return GL_INT;
			case ElementType::Int3:   return GL_INT;
			case ElementType::Int4:   return GL_INT;
			case ElementType::Float:  return GL_FLOAT;
			case ElementType::Float2: return GL_FLOAT;
			case ElementType::Float3: return GL_FLOAT;
			case ElementType::Float4: return GL_FLOAT;
			case ElementType::Mat3:	  return GL_FLOAT;
			case ElementType::Mat4:   return GL_FLOAT;
			case ElementType::Bool:   return GL_BOOL;
		}

		AL_ENGINE_ASSERT(false, "The provided element type is not supported");
		return 0;
	}

	struct BufferElement
	{
		BufferElement(ElementType type, const std::string& name, bool isNormalized = false) :
			Type(type), Name(name), Size(GetSize(type)), IsNormalized(isNormalized), Offset(0)
		{ }

		uint32_t Size;
		uint32_t Offset;
		ElementType Type;
		std::string Name;
		bool IsNormalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		uint32_t GetStride() const;

		constexpr std::vector<BufferElement>::const_iterator begin() const;
		constexpr std::vector<BufferElement>::const_iterator end() const;

	private:
		std::vector<BufferElement> elements;
		uint32_t stride;

		void ConstructLayout();
	};
}


