#include "ShaderProgram.h"

#include <iostream>
#include <filesystem>

#include "glm/gtc/type_ptr.hpp"

#include "Resources/ResourceAllocator.hpp"

namespace Alpha
{
	ShaderProgram::ShaderProgram(const std::string& path) : ShaderProgram()
	{
		for (const auto& entry : std::filesystem::directory_iterator(path))
		{
			auto shader = Resources::ResourceAllocator<Shader>::Get().Add(entry.path().string());

			glAttachShader(programId, shader->shaderId);
		}

		Link();
	}

	ShaderProgram::ShaderProgram(std::initializer_list<const Shader> shaders) :
		ShaderProgram()
	{
		for (const auto& shader : shaders)
		{
			glAttachShader(programId, shader.shaderId);
		}

		Link();
	}

	ShaderProgram::ShaderProgram()
	{
		programId = glCreateProgram();

		if (!programId)
		{
			std::cerr << "failed to create shader program" << std::endl;
			return;
		}
	}

	void ShaderProgram::Use()
	{
		glUseProgram(programId);
	}

	void ShaderProgram::Detach()
	{
		glUseProgram(programId);
	}

	void ShaderProgram::SetUniformMatrix4f(const char* name, glm::mat4 value)
	{
		GLint location = glGetUniformLocation(programId, name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void ShaderProgram::SetUniformInt(const char* name, int value)
	{
		GLint location = glGetUniformLocation(programId, name);
		glUniform1i(location, value);
	}

	void ShaderProgram::SetUniformIntPointer(const char* name, int *value, size_t size)
	{
		GLint location = glGetUniformLocation(programId, name);
		glUniform1iv(location, size, value);
	}

	GLuint ShaderProgram::GetUniformLocation(const char* name)
	{
		return glGetUniformLocation(programId, name);
	}

	void ShaderProgram::Link()
	{
		glLinkProgram(programId);

		GLint result;
		glGetProgramiv(programId, GL_LINK_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetProgramInfoLog(programId, sizeof(errorBuffer), NULL, errorBuffer);
			std::cerr << "program link failed with: " << errorBuffer << std::endl;
			return;
		}

		glValidateProgram(programId);

		glGetProgramiv(programId, GL_VALIDATE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetProgramInfoLog(programId, sizeof(errorBuffer), NULL, errorBuffer);
			std::cerr << "program validate failed with: " << errorBuffer << std::endl;
			return;
		}
	}
}
