#pragma once

#include <stdint.h>

#include "GL/glew.h"
#include "Render/IndexBuffer.h"

namespace Alpha
{
	class OpenGLIndexBuffer : public Alpha::IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32_t* buffer, uint32_t size);
		OpenGLIndexBuffer(uint32_t size);

		~OpenGLIndexBuffer();

		void Bind() override;
		void Unbind() override;

		uint32_t GetAmountOfElements() const override;

	private:
		OpenGLIndexBuffer();

		GLuint id;
		uint32_t size;
	};
}


