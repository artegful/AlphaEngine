#pragma once

#include <stdint.h>

#include "GL/glew.h"
#include "Render/IndexBuffer.h"

namespace Alpha
{
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* buffer, std::size_t count);
		OpenGLIndexBuffer(uint32_t count);

		~OpenGLIndexBuffer();

		void Bind() override;
		void Unbind() override;

		uint32_t GetAmountOfElements() const override;

	private:
		OpenGLIndexBuffer();

		GLuint id;
		uint32_t count;
	};
}


