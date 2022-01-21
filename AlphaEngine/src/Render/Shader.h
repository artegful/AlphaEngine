#pragma once

#include <string>
#include <unordered_map>

#include "GL/glew.h"

namespace Alpha
{
	class Shader
	{
	public:
		Shader(const std::string& fileName);
		Shader(const std::string& fileName, GLenum shaderType);

		~Shader() = default;

	private:
		Shader(GLenum shaderType);

		const static std::unordered_map<std::string, GLenum> ExtensionToType;
		GLuint shaderId;

		void CompileShader(const std::string& source);
		GLenum GetShaderType(const std::string& filePath);

		friend class ShaderProgram;
	};

}

