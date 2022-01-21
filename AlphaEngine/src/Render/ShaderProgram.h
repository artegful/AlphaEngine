#pragma once

#include "GL/glew.h"
#include "glm/mat4x4.hpp"

#include "Shader.h"

namespace Alpha
{
	class ShaderProgram
	{
	public:
		ShaderProgram(const std::string& path);
		ShaderProgram(std::initializer_list<const Shader> files);

		void Use();
		void Detach();
		GLuint GetUniformLocation(const char* name);

		void SetUniformMatrix4f(const char* name, glm::mat4 value);
		void SetUniformInt(const char* name, int value);
		void SetUniformIntPointer(const char* name, int *value, size_t size);

	private:
		ShaderProgram();

		GLuint programId;

		void Link();
	};
}

