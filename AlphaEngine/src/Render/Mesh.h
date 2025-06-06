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

        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material, unsigned int instanceTransformsBuffer);
        
        void Draw(Shader& shader, unsigned int amount);

    private:
        unsigned int VBO, EBO, VAO, instanceTransformsBuffer;
        Material material;

        void SetupMesh();
        void BindMaterial(Shader& shader);
        inline bool IsSetup() { return VAO != 0; }
    };
}