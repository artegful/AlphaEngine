#include "OpenGLShader.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Core/Core.h"
#include "glm/gtc/type_ptr.hpp"
#include "Utils/Utils.h"

using namespace std::string_literals;

namespace Alpha
{
	const std::unordered_map<GLenum, std::string> OpenGLShader::ShaderTypeToDefine
	{ 
		{ GL_VERTEX_SHADER, "VERTEX" },
		{ GL_FRAGMENT_SHADER, "FRAGMENT" }
	};

	const std::unordered_map<Shader::ShaderType, GLenum> OpenGLShader::ShaderTypeToOpenGLType
	{
		{ Shader::ShaderType::Vertex, GL_VERTEX_SHADER },
		{ Shader::ShaderType::Fragment, GL_FRAGMENT_SHADER }
	};

	const std::string OpenGLShader::TypeSpecifier = "#type";

	OpenGLShader::OpenGLShader(const std::string& path) : OpenGLShader()
	{
		name = Utils::GetNameFromPath(path);

		std::string source = ReadFile(path);

		auto versionStart = source.find("#version");
		AL_ASSERT(versionStart != std::string::npos, "Shader file must include version directive");

		auto versionLineEnd = source.find("\r\n", versionStart);

		std::string versionLine = source.substr(versionStart, versionLineEnd - versionStart + 2);
		source.erase(versionStart, versionLineEnd);

		for (auto& [key, value] : ShaderTypeToDefine)
		{
			if (source.find(value) != std::string::npos)
			{
				AddShader(source, key, versionLine);
			}
		}

		Link();
	}

	void OpenGLShader::Bind()
	{
		glUseProgram(id);
	}

	void OpenGLShader::Unbind()
	{
		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform1i(location, value);
	}

	void OpenGLShader::SetIntArray(const std::string& name, int values[], size_t amount)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform1iv(location, amount, values);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform4fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	OpenGLShader::OpenGLShader()
	{
		id = glCreateProgram();
	}

	void OpenGLShader::AddShader(const std::string& source, const GLenum shaderType, const std::string& versionLine)
	{
		std::string defineTypeLine = "#define "s + ShaderTypeToDefine.at(shaderType) + "\r\n";

		const GLchar* sources[3] = { versionLine.data(), defineTypeLine.data(), source.c_str() };
		const GLint lengths[3] = { (int)versionLine.size(), (int)defineTypeLine.size(), (int)source.size() };

		GLuint shaderId = glCreateShader(shaderType);

		glShaderSource(shaderId, 3, sources, lengths);
		glCompileShader(shaderId);

		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetShaderInfoLog(shaderId, sizeof(errorBuffer), NULL, errorBuffer);
			AL_ASSERT(false, "shader compilation failed with: "s + errorBuffer);
			return;
		}

		glAttachShader(id, shaderId);
	}

	std::string OpenGLShader::ReadFile(const std::string& path)
	{
		std::ifstream fileStream(path, std::ios::binary | std::ios::ate);
		AL_ASSERT(fileStream.is_open(), "Cannot open shader file");

		if (fileStream.is_open())
		{
			std::streampos size = fileStream.tellg();
			std::string content(size, ' ');

			fileStream.seekg(0);
			fileStream.read(content.data(), size);

			return content;
		}

		return "";
	}

	void OpenGLShader::Link()
	{
		glLinkProgram(id);

		GLint result;
		glGetProgramiv(id, GL_LINK_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetProgramInfoLog(id, sizeof(errorBuffer), NULL, errorBuffer);
			AL_ASSERT(false, "program link failed with: "s + errorBuffer);
			return;
		}

		glValidateProgram(id);

		glGetProgramiv(id, GL_VALIDATE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetProgramInfoLog(id, sizeof(errorBuffer), NULL, errorBuffer);
			AL_ASSERT(false, "program validate failed with: "s + errorBuffer);
			return;
		}
	}
}

