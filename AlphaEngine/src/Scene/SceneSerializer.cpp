#include "SceneSerializer.h"

#include <fstream>
#include <sstream>
#include "yaml-cpp/yaml.h"

#include "Scene.h"
#include "ECS/Entity.h"
#include "Resources/ResourceAllocator.hpp"

#include "Components/NameComponent.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Render/Sprite.h"
#include "Components/OrthoCameraComponent.h"
#include "Components/Rigidbody2DComponent.h"
#include "Components/Box2DColliderComponent.h"

#include "rttr/type.h"

namespace YAML
{
	YAML::Emitter& operator <<(YAML::Emitter& yaml, const glm::vec2& vector)
	{
		yaml << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << YAML::EndSeq;

		return yaml;
	}

	template<>
	struct convert<glm::vec2>
	{
		static bool decode(const Node& node, glm::vec2& vector)
		{
			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();

			return true;
		}
	};

	YAML::Emitter& operator <<(YAML::Emitter& yaml, const glm::vec3& vector)
	{
		yaml << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << YAML::EndSeq;

		return yaml;
	}

	template<>
	struct convert<glm::vec3>
	{
		static bool decode(const Node& node, glm::vec3& vector)
		{
			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();
			vector.z = node[2].as<float>();
			
			return true;
		}
	};

	YAML::Emitter& operator <<(YAML::Emitter& yaml, const glm::vec4& vector)
	{
		yaml << YAML::Flow << YAML::BeginSeq << vector.x << vector.y << vector.z << vector.w << YAML::EndSeq;

		return yaml;
	}

	template<>
	struct convert<glm::vec4>
	{
		static bool decode(const Node& node, glm::vec4& vector)
		{
			vector.x = node[0].as<float>();
			vector.y = node[1].as<float>();
			vector.z = node[2].as<float>();
			vector.w = node[3].as<float>();

			return true;
		}
	};
}

namespace Alpha
{
	void SerializeEntity(YAML::Emitter& yaml, Entity entity)
	{
		yaml << YAML::BeginMap;

		yaml << YAML::Key << "Entity" << YAML::Value << "43325";

		yaml << YAML::Key << "Name";
		std::string name = entity.GetComponent<NameComponent>().Name;
		yaml << YAML::Value << name;

		Transform transform = entity.GetComponent<TransformComponent>();
		yaml << YAML::Key << "TransformComponent";
		yaml << YAML::BeginMap;
		yaml << YAML::Key << "Position" << YAML::Value << transform.Position;
		yaml << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
		yaml << YAML::Key << "Scale" << YAML::Value << transform.Scale;
		yaml << YAML::EndMap;

		if (entity.HasComponent<SpriteComponent>())
		{
			SpriteComponent& spriteComponent = entity.GetComponent<SpriteComponent>();
			yaml << YAML::Key << "SpriteComponent";
			yaml << YAML::BeginMap;
			yaml << YAML::Key << "Color" << YAML::Value << spriteComponent.Color;

			if (spriteComponent.Sprite != nullptr)
			{
				std::shared_ptr<Sprite> sprite = spriteComponent.Sprite;

				yaml << YAML::Key << "Sprite";
				yaml << YAML::BeginMap;

				yaml << YAML::Key << "Uvs";
				yaml << YAML::Flow << YAML::BeginSeq;
				const glm::vec2* uvs = sprite->GetUvs();
				for (auto i = 0; i < 4; i++)
				{
					yaml << uvs[i];
				}
				yaml << YAML::EndSeq;
				
				if (sprite->HasTexture())
				{
					yaml << YAML::Key << "Texture" << YAML::Value << sprite->GetTexture()->GetPath();
				}

				yaml << YAML::EndMap;
			}

			yaml << YAML::EndMap;
		}

		if (entity.HasComponent<OrthoCameraComponent>())
		{
			auto& cameraComponent = entity.GetComponent<OrthoCameraComponent>();

			yaml << YAML::Key << "OrthoCameraComponent";
			yaml << YAML::BeginMap;

			yaml << YAML::Key << "Size" << YAML::Value << cameraComponent.Camera.GetSize();
			yaml << YAML::Key << "Zoom" << YAML::Value << cameraComponent.Camera.GetZoom();

			yaml << YAML::EndMap;
		}

		if (entity.HasComponent<Rigidbody2DComponent>())
		{
			auto& rigidbody2DComponent = entity.GetComponent<Rigidbody2DComponent>();

			yaml << YAML::Key << "Rigidbody2DComponent";
			yaml << YAML::BeginMap;

			yaml << YAML::Key << "Type" << YAML::Value << static_cast<int>(rigidbody2DComponent.Type);
			yaml << YAML::Key << "IsFixedRotation" << YAML::Value << rigidbody2DComponent.IsFixedRotation;

			yaml << YAML::EndMap;
		}

		if (entity.HasComponent<Box2DColliderComponent>())
		{
			auto& box2DComponent = entity.GetComponent<Box2DColliderComponent>();

			yaml << YAML::Key << "Box2DColliderComponent";
			yaml << YAML::BeginMap;

			yaml << YAML::Key << "Offset" << YAML::Value << box2DComponent.Offset;
			yaml << YAML::Key << "Size" << YAML::Value << box2DComponent.Size;
			yaml << YAML::Key << "Density" << YAML::Value << box2DComponent.Density;
			yaml << YAML::Key << "Friction" << YAML::Value << box2DComponent.Friction;
			yaml << YAML::Key << "Restitution" << YAML::Value << box2DComponent.Restitution;
			yaml << YAML::Key << "RestitutionThreshold" << YAML::Value << box2DComponent.RestitutionThreshold;

			yaml << YAML::EndMap;
		}

		yaml << YAML::EndMap;
	}

	void SceneSerializer::DeserializeEntity(const YAML::Node& yaml)
	{
		std::string name = yaml["Name"].as<std::string>();

		Entity entity = scene->CreateEntity(name);

		TransformComponent& transformComponent = entity.GetComponent<TransformComponent>();
		const YAML::Node& transformNode = yaml["TransformComponent"];
		transformComponent.Transform.Position = transformNode["Position"].as<glm::vec3>();
		transformComponent.Transform.Rotation = transformNode["Rotation"].as<glm::vec3>();
		transformComponent.Transform.Scale = transformNode["Scale"].as<glm::vec3>();

		const YAML::Node& spriteComponentNode = yaml["SpriteComponent"];
		if (spriteComponentNode)
		{
			SpriteComponent& spriteComponent = entity.AddComponent<SpriteComponent>();
			spriteComponent.Color = spriteComponentNode["Color"].as<glm::vec4>();

			const YAML::Node& spriteNode = spriteComponentNode["Sprite"];
			if (spriteNode)
			{
				glm::vec2 uvs[4];
				const YAML::Node& uvsNode = spriteNode["Uvs"];

				for (auto i = 0; i < 4; i++)
				{
					uvs[i] = uvsNode[i].as<glm::vec2>();
				}

				std::string path = spriteNode["Texture"].as<std::string>();
				std::shared_ptr<Texture> textureResource = ResourceAllocator<Texture>::Get(path);

				spriteComponent.Sprite = Sprite::Create(textureResource, uvs);
			}
		}

		const YAML::Node& cameraComponentNode = yaml["OrthoCameraComponent"];
		if (cameraComponentNode)
		{
			glm::vec2 serializedSize = cameraComponentNode["Size"].as<glm::vec2>();
			OrthoCameraComponent& cameraComponent = entity.AddComponent<OrthoCameraComponent>(OrthoCamera(serializedSize));

			float zoom = cameraComponentNode["Zoom"].as<float>();
			cameraComponent.Camera.SetZoom(zoom);
		}

		const YAML::Node& rigidbody2DComponentNode = yaml["Rigidbody2DComponent"];
		if (rigidbody2DComponentNode)
		{
			Rigidbody2DComponent& rigidbody2DComponent = entity.AddComponent<Rigidbody2DComponent>();

			rigidbody2DComponent.IsFixedRotation = rigidbody2DComponentNode["IsFixedRotation"].as<bool>();
			rigidbody2DComponent.Type = static_cast<Alpha::Rigidbody2DComponent::BodyType>(rigidbody2DComponentNode["Type"].as<int>());
		}

		const YAML::Node& Box2DColliderComponentNode = yaml["Box2DColliderComponent"];
		if (Box2DColliderComponentNode)
		{
			Box2DColliderComponent& box2DComponent = entity.AddComponent<Box2DColliderComponent>();

			box2DComponent.Offset = Box2DColliderComponentNode["Offset"].as<glm::vec2>();
			box2DComponent.Size = Box2DColliderComponentNode["Size"].as<glm::vec2>();
			box2DComponent.Density = Box2DColliderComponentNode["Density"].as<float>();
			box2DComponent.Friction = Box2DColliderComponentNode["Friction"].as<float>();
			box2DComponent.Restitution = Box2DColliderComponentNode["Restitution"].as<float>();
			box2DComponent.RestitutionThreshold = Box2DColliderComponentNode["RestitutionThreshold"].as<float>();
		}
	}

	SceneSerializer::SceneSerializer(Scene* scene) :
		scene(scene)
	{ }

	void SceneSerializer::Serialize(const std::string& filePath)
	{
		YAML::Emitter yaml;

		yaml << YAML::BeginMap;
		yaml << YAML::Key << "Version" << YAML::Value << 1;
		yaml << YAML::Key << "Scene" << YAML::Value << "some name here";

		yaml << YAML::Key << "Entities" << YAML::BeginSeq;

		scene->registry.each([&](auto entity)
			{
				SerializeEntity(yaml, Entity{ scene, entity });
			});
		
		yaml << YAML::EndSeq;
		yaml << YAML::EndMap;

		std::ofstream outputFile(filePath);
		outputFile << yaml.c_str();
	}

	void SceneSerializer::Deserialize(const std::string& filePath)
	{
		std::ifstream inputFile(filePath);
		std::stringstream input;
		input << inputFile.rdbuf();

		YAML::Node yaml = YAML::Load(input.str());

		YAML::Node entities = yaml["Entities"];

		for (YAML::const_iterator it = entities.begin(); it != entities.end(); it++)
		{
			DeserializeEntity(*it);
		}
	}
}
