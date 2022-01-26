#pragma once

#include <string>
#include <unordered_map>

#include "GL/glew.h"
#include "Render/Shader.h"

namespace Alpha
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& fileName);
		OpenGLShader(const std::string& name, const std::unordered_map<ShaderType, const std::string>& shaderSources);

		void Bind();
		void Unbind();

		void SetUniformInt(const std::string& name, int value);
		void SetUniformIntArray(const std::string& name, int values[], size_t amount);
		void SetUniformFloat3(const std::string& name, glm::vec3& value);
		void SetUniformMat4(const std::string& name, const glm::mat4& value);

	private:
		OpenGLShader();

		const static std::string TypeSpecifier;
		const static std::unordered_map<std::string, GLenum> ShaderTypeSpecifierToType;
		const static std::unordered_map<ShaderType, GLenum> ShaderTypeToOpenGLType;
		
		std::string name;
		GLuint id;

		void AddShader(const std::string& source, const GLenum shaderType);
		std::string GetNameFromPath(const std::string& path);
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> Parse(const std::string& source);
		GLenum GetShaderType(const std::string& filePath);
		void Link();
	};

}

