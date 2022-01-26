#pragma once

#include <vector>
#include <memory>

#include "GL/glew.h"
#include "Shader.h"

namespace Alpha
{
	class Texture;

	struct TransformComponent;
	struct SpriteComponent;
	struct CameraComponent;

	class SpriteBatch
	{
	public:
		SpriteBatch();

		bool HasSpace() const;
		bool HasTexture(const std::shared_ptr<Texture>& texture) const;
		bool HasTextureSpace() const;

		void AddSprite(const SpriteComponent& sprite, const TransformComponent& transform);
		void Draw(CameraComponent camera, TransformComponent cameraTransform);

	private:
		struct QuadVertex
		{
			glm::vec3 Position;
			glm::vec4 Color;
			glm::vec2 Uv;
			int TextureId;
		};

		static constexpr size_t MAX_SPRITES = 100;
		static constexpr size_t VERTICES_IN_SPRITE = 4;
		static constexpr size_t INDICES_IN_SPRITE = 6;
		static constexpr size_t MAX_TEXTURES = 8;

		QuadVertex vertexBuffer[MAX_SPRITES * VERTICES_IN_SPRITE];
		GLuint indexBuffer[MAX_SPRITES * INDICES_IN_SPRITE];
		std::vector<std::shared_ptr<Texture>> textures;

		unsigned int amountStored;

		GLuint vaoId;
		GLuint vboId;
		GLuint eboId;

		std::shared_ptr<Shader> shader;

		void GenerateIndexBuffer();
	};
}

