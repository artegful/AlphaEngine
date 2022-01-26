#include "OpenGLShader.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Core/Core.h"
#include "glm/gtc/type_ptr.hpp"
#include "Utils/Utils.h"

namespace Alpha
{
	const std::unordered_map<std::string, GLenum> OpenGLShader::ShaderTypeSpecifierToType
	{ 
		{ "vert", GL_VERTEX_SHADER }, 
		{ "frag", GL_FRAGMENT_SHADER }
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
		std::unordered_map<GLenum, std::string> openGLShaderToSource = Parse(source);

		for (auto& [type, source] : openGLShaderToSource)
		{
			AddShader(source, type);
		}

		Link();
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::unordered_map<ShaderType, const std::string>& shaderSources) : OpenGLShader(name)
	{
		this->name = name;

		for (auto& [type, source] : shaderSources)
		{
			AddShader(source, ShaderTypeToOpenGLType.at(type));
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

	void OpenGLShader::SetUniformInt(const std::string& name, int value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform1i(location, value);
	}

	void OpenGLShader::SetUniformIntArray(const std::string& name, int values[], size_t amount)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform1iv(location, amount, values);
	}

	void OpenGLShader::SetUniformFloat3(const std::string& name, glm::vec3& value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniform3fv(location, 1, glm::value_ptr(value));
	}

	void OpenGLShader::SetUniformMat4(const std::string& name, const glm::mat4& value)
	{
		GLint location = glGetUniformLocation(id, name.data());

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	OpenGLShader::OpenGLShader()
	{
		id = glCreateProgram();
	}

	void OpenGLShader::AddShader(const std::string& source, const GLenum shaderType)
	{
		const GLchar* sources[1] = { source.c_str() };

		const GLint lengths[1] = { (int) source.size() };

		GLuint shaderId = glCreateShader(shaderType);

		glShaderSource(shaderId, 1, sources, lengths);
		glCompileShader(shaderId);

		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetShaderInfoLog(shaderId, sizeof(errorBuffer), NULL, errorBuffer);
			AL_ASSERT(false, std::string("shader compilation failed with: ") + errorBuffer);
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

	std::unordered_map<GLenum, std::string> OpenGLShader::Parse(const std::string& source)
	{
		size_t previousEnd = 0;
		std::unordered_map<GLenum, std::string> shaders;
		size_t specifier = source.find(TypeSpecifier, previousEnd);

		//AL_ASSERT(specifier != std::string::npos, std::string("Shader ") + name + " is empty");

		while (specifier != std::string::npos)
		{
			size_t endOfLine = source.find("\r\n", specifier);
			size_t startOfType = specifier + TypeSpecifier.length() + 1;
			std::string type = source.substr(startOfType, endOfLine - startOfType);

			specifier = source.find(TypeSpecifier, endOfLine);
			size_t endOfSourceCode = specifier == std::string::npos ? source.length() : specifier;

			//remove all spaces
			type.erase(std::remove(type.begin(), type.end(), ' '), type.end());
			GLenum shaderType = GetShaderType(type);

			AL_ASSERT(!shaders.contains(shaderType), std::string("Can't have multiple shaders on one type in shader ") + name);

			size_t startOfSource = endOfLine + 1;
			shaders[shaderType] = source.substr(startOfSource, endOfSourceCode - startOfSource);
		}

		return shaders;
	}

	GLenum OpenGLShader::GetShaderType(const std::string& word)
	{
		AL_ENGINE_ASSERT(ShaderTypeSpecifierToType.contains(word), word + " shader type is not supported or invalid");

		return ShaderTypeSpecifierToType.at(word);
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
			AL_ASSERT(false, std::string("program link failed with: ") + errorBuffer);
			return;
		}

		glValidateProgram(id);

		glGetProgramiv(id, GL_VALIDATE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetProgramInfoLog(id, sizeof(errorBuffer), NULL, errorBuffer);
			AL_ASSERT(false, std::string("program validate failed with: ") + errorBuffer);
			return;
		}
	}
}

