#pragma once

#include <vector>
#include "Texture.h"
#include "Vertex.h"
#include "Shader.h"
#include "Material.h"

namespace Alpha
{
    class Mesh 
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<std::shared_ptr<Texture>> textures;
        unsigned int VAO;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures);
        
        void Draw(Shader& shader);

    private:
        unsigned int VBO, EBO;
        Material material;

        void SetupMesh();
        inline bool IsSetup() { return VAO != 0; }
    };
}