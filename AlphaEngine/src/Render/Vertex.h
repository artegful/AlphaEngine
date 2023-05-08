#pragma once

#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

#define MAX_BONE_INFLUENCE 4

namespace Alpha
{
    struct Vertex 
    {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
}