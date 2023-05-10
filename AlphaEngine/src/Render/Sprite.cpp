#include "Sprite.h"

namespace Alpha
{
    Sprite::Sprite(const std::shared_ptr<Texture> texture, const glm::vec2 uvs[4]) :
        texture(texture)
    {
        memcpy(uvCoords, uvs, 4 * sizeof(glm::vec2));
    }

    Sprite::Sprite(const std::shared_ptr<Texture> texture) :
        texture(texture)
    { }

    const glm::vec2* Sprite::GetUvs() const
    {
        return uvCoords;
    }

    std::shared_ptr<Texture> Sprite::GetTexture() const
    {
        return texture;
    }

    bool Sprite::HasTexture() const
    {
        return texture != nullptr;
    }

    std::shared_ptr<Sprite> Sprite::CreateFromSize(const std::shared_ptr<Alpha::Texture> spriteSheet, const glm::ivec2 spriteCoodsInCells,
        const glm::ivec2 cellSizeInPixels, const glm::i8vec2 spriteSizeInCells)
    {
        glm::vec2 uvs[4]
        {
            { spriteCoodsInCells.x * cellSizeInPixels.x / (float)spriteSheet->GetWidth(), spriteCoodsInCells.y * cellSizeInPixels.y / (float)spriteSheet->GetHeight() },
            { (spriteCoodsInCells.x + spriteSizeInCells.x) * cellSizeInPixels.x / (float)spriteSheet->GetWidth(), spriteCoodsInCells.y * cellSizeInPixels.y / (float)spriteSheet->GetHeight() },
            { (spriteCoodsInCells.x + spriteSizeInCells.x) * cellSizeInPixels.x / (float)spriteSheet->GetWidth(), (spriteCoodsInCells.y + spriteSizeInCells.y) * cellSizeInPixels.y / (float)spriteSheet->GetHeight() },
            { spriteCoodsInCells.x * cellSizeInPixels.x / (float)spriteSheet->GetWidth(), (spriteCoodsInCells.y + spriteSizeInCells.y) * cellSizeInPixels.y / (float)spriteSheet->GetHeight() }
        };

        return std::make_shared<Sprite>(spriteSheet, uvs);
    }

    std::shared_ptr<Sprite> Sprite::CreateFromCount(const std::shared_ptr <Alpha::Texture> spriteSheet, const glm::ivec2 spriteCoodsInCells,
        const glm::ivec2 amountOfCells, const glm::i8vec2 spriteSizeInCells)
    {
        glm::ivec2 cellSizeInPixels = { spriteSheet->GetWidth() / amountOfCells.x, spriteSheet->GetHeight() / amountOfCells.y };

        return CreateFromSize(spriteSheet, spriteCoodsInCells, cellSizeInPixels, spriteSizeInCells);
    }

    std::shared_ptr<Sprite> Sprite::Create(const std::shared_ptr<Texture> texture, const glm::vec2 uvs[4])
    {
        return std::make_shared<Sprite>(texture, uvs);
    }

    std::shared_ptr<Sprite> Sprite::Create(const std::shared_ptr<Texture> texture)
    {
        return std::make_shared<Sprite>(texture);
    }

}
