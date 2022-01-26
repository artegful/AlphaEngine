#include "Sprite.h"

namespace Alpha
{
    Sprite::Sprite(std::shared_ptr<Texture>& texture) :
        texture(texture), 
        uvCoords { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), 
                   glm::vec2(1.0f, 1.0f), glm::vec2(0.0f, 1.0f) }
    { }

    Sprite::Sprite(std::shared_ptr<Texture>& texture, glm::vec2 uvCoords[4]) :
        texture(texture)
    {
        memcpy(this->uvCoords, uvCoords, sizeof(uvCoords));
    }

    const glm::vec2* Sprite::GetUvCoords() const
    {
        return uvCoords;
    }

    std::shared_ptr<Texture> Sprite::GetTexture() const
    {
        return texture;
    }
}
