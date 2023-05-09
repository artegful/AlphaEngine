#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include "glm/glm.hpp"

namespace Alpha
{
	struct Material;

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
		virtual uint32_t GetId() const = 0;
		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat(const std::string& name, float value) = 0;
		virtual void SetIntArray(const std::string& name, int values[], size_t amount) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
		virtual void SetMaterial(const Material& material) = 0;

		//TODO write all remaining uniforms

		static std::shared_ptr<Shader> Create(const std::string& path);
	};
}