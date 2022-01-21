#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace Alpha
{
	const std::unordered_map<std::string, GLenum> Shader::ExtensionToType
	{ 
		{ "vert", GL_VERTEX_SHADER }, 
		{ "frag", GL_FRAGMENT_SHADER }
	};

	Shader::Shader(const std::string& fileName) : Shader(fileName, GetShaderType(fileName))
	{ }

	Shader::Shader(const std::string& fileName, GLenum shaderType) :
		Shader(shaderType)
	{
		std::ifstream fileStream(fileName);

		if (fileStream.is_open())
		{
			std::stringstream stringStream;

			stringStream << fileStream.rdbuf();

			CompileShader(stringStream.str());
		}
		else
		{
			throw std::invalid_argument(std::string("No such file: ") + fileName);
		}
	}

	Shader::Shader(GLenum shaderType)
	{
		shaderId = glCreateShader(shaderType);
	}

	void Shader::CompileShader(const std::string& source)
	{
		const GLchar* sources[1] = { source.c_str() };

		const GLint lengths[1] = { (int) source.size() };

		glShaderSource(shaderId, 1, sources, lengths);
		glCompileShader(shaderId);

		GLint result;
		glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			GLchar errorBuffer[1024]{ 0 };

			glGetShaderInfoLog(shaderId, sizeof(errorBuffer), NULL, errorBuffer);
			std::cerr << "shader compilation failed with: " << errorBuffer << std::endl;
			return;
		}
	}

	GLenum Shader::GetShaderType(const std::string& filePath)
	{
		const std::string extension = filePath.substr(filePath.find_last_of(".") + 1);

		if (ExtensionToType.find(extension) == ExtensionToType.end())
		{
			throw std::invalid_argument("shader type " + extension + " is not supported");
		}

		return ExtensionToType.at(extension);
	}
}

