#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "glm/glm.hpp"

namespace Alpha
{
	class Shader
	{
	public:

		enum class ShaderType 
		{
			Vertex,
			Fragment
		};

		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		//TODO move to material system later
		virtual void SetUniformInt(const std::string& name, int value) = 0;
		virtual void SetUniformIntArray(const std::string& name, int values[], size_t amount) = 0;
		virtual void SetUniformFloat3(const std::string& name, glm::vec3& value) = 0;
		virtual void SetUniformMat4(const std::string& name, const glm::mat4& value) = 0;

		//TODO write all remaining uniforms

		static std::shared_ptr<Shader> Create(const std::string& path);
		static std::shared_ptr<Shader> Create(const std::string& name, const std::unordered_map<ShaderType, const std::string>& shaderSources);
	};
}