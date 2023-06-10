#include "Mesh.h"

#include <string>
#include "GL/glew.h"
#include "RenderConstants.h"

namespace Alpha
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const Material& material, unsigned int instanceTransformsBuffer) :
        vertices(vertices), indices(indices), material(material), VAO(0), VBO(0), EBO(0), instanceTransformsBuffer(instanceTransformsBuffer)
	{ }

	void Mesh::Draw(Shader& shader, unsigned int amount)
	{
        if (!IsSetup())
        {
            SetupMesh();
        }

        BindMaterial(shader);

        glBindVertexArray(VAO);
        glDrawElementsInstanced(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0, amount);
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

        glBindBuffer(GL_ARRAY_BUFFER, instanceTransformsBuffer);

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
        glEnableVertexAttribArray(5);
        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
        glEnableVertexAttribArray(6);
        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

        glVertexAttribDivisor(3, 1);
        glVertexAttribDivisor(4, 1);
        glVertexAttribDivisor(5, 1);
        glVertexAttribDivisor(6, 1);

        glBindVertexArray(0);
	}

    void Mesh::BindMaterial(Shader& shader)
    {
        if (material.DiffuseMap)
        {
            material.DiffuseMap->Bind(0);
            shader.SetInt("material.diffuse", 0);
        }
        else 
        {
            shader.SetInt("material.diffuse", RenderConstants::DEFAULT_TEXTURE_SLOT);
        }

        if (material.SpecularMap)
        {
            material.SpecularMap->Bind(1);
            shader.SetInt("material.specular", 1);
        }
        else
        {
            shader.SetInt("material.specular", RenderConstants::DEFAULT_TEXTURE_SLOT);
        }

        shader.SetFloat("material.minSpecular", material.SpecularMap ? 0.0f : 0.4f);
        shader.SetFloat("material.shininess", material.Shininess);
        shader.SetFloat3("material.diffuseColor", material.DiffuseColor);
    }
}
