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

		void Bind() override;
		void Unbind() override;

		uint32_t GetId() const override;
		void SetInt(const std::string& name, int value) override;
		void SetIntArray(const std::string& name, int values[], size_t amount) override;
		void SetFloat3(const std::string& name, const glm::vec3& value) override;
		void SetFloat4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;

	private:
		OpenGLShader();

		const static std::string TypeSpecifier;
		const static std::unordered_map<GLenum, std::string> ShaderTypeToDefine;
		const static std::unordered_map<ShaderType, GLenum> ShaderTypeToOpenGLType;
		
		std::string name;
		GLuint id;

		void AddShader(const std::string& source, const GLenum shaderType, const std::string& versionLine);
		std::string ReadFile(const std::string& path);
		std::unordered_map<GLenum, std::string> Parse(const std::string& source);
		GLenum GetShaderType(const std::string& filePath);
		void Link();
	};

}

