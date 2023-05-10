#include "Mesh.h"

#include <string>
#include "GL/glew.h"
#include <iostream>

namespace Alpha
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<std::shared_ptr<Texture>>& textures) :
        vertices(vertices), indices(indices), VAO(0), VBO(0), EBO(0)
	{
        for (const auto& texture : textures)
        {
            std::string name = texture->GetType();

            if (name == "texture_diffuse" && !material.DiffuseMap)
            {
                material.DiffuseMap = texture;
            }
            else if (name == "texture_specular" && !material.SpecularMap)
            {
                material.SpecularMap = texture;
            }

            //"texture_normal" and "texture_height"
        }
    }

	void Mesh::Draw(Shader& shader)
	{
        if (!IsSetup())
        {
            SetupMesh();
        }

        BindMaterial(shader);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glActiveTexture(GL_TEXTURE0);
	}

	void Mesh::SetupMesh()
	{
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glBindVertexArray(0);
	}

    void Mesh::BindMaterial(Shader& shader)
    {
        if (material.DiffuseMap)
        {
            material.DiffuseMap->Bind(0);
            shader.SetInt("material.diffuse", 0);
        }

        if (material.SpecularMap)
        {
            material.SpecularMap->Bind(1);
            shader.SetInt("material.specular", 1);
        }

        shader.SetFloat("material.minSpecular", material.SpecularMap ? 0.0f : 0.4f);
        shader.SetFloat("material.shininess", material.Shininess);
    }
}
