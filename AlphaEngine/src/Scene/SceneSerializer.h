#pragma once

#include <string>

namespace YAML
{
	class Node;
}

namespace Alpha
{
	class Scene;

	class SceneSerializer
	{
	public:
		explicit SceneSerializer(Scene* scene);
		void Serialize(const std::string& filePath);
		void Deserialize(const std::string& filePath);

	private:
		Scene* scene;

		void DeserializeEntity(const YAML::Node& yaml);
	};
}