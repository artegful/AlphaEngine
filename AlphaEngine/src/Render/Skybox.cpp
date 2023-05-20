#include "Skybox.h"

#include "VertexBuffer.h"
#include "BufferLayout.h"
#include "Shader.h"
#include <stb_image.h>
#include <Resources/ResourceAllocator.hpp>

namespace Alpha
{
	Skybox::Skybox(const std::array<std::string, 6>& texturePaths) : texturePaths(texturePaths)
	{ }

    void Skybox::Draw()
    {
        if (!vertexArray)
        {
            Initialise();
        }

        glDepthFunc(GL_LEQUAL);
        vertexArray->Bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        vertexArray->Unbind();

        glDepthFunc(GL_LESS);
    }

    void Skybox::Initialise()
    {
        std::array skyboxVertices = {
            -1.0f,  1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f, -1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f, -1.0f,  1.0f,
            -1.0f, -1.0f,  1.0f,

            -1.0f,  1.0f, -1.0f,
             1.0f,  1.0f, -1.0f,
             1.0f,  1.0f,  1.0f,
             1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f,  1.0f,
            -1.0f,  1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f, -1.0f,
             1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f,  1.0f,
             1.0f, -1.0f,  1.0f
        };

        vertexArray = VertexArray::Create();
        std::shared_ptr<VertexBuffer> vertexBuffer = VertexBuffer::Create(skyboxVertices.data(), sizeof(skyboxVertices));
        vertexBuffer->SetLayout(std::shared_ptr<BufferLayout>(new BufferLayout{ { ElementType::Float3, "vPos" } }));

        vertexArray->AddVertexBuffer(vertexBuffer);

        LoadTextures(texturePaths);
    }

    void Skybox::LoadTextures(const std::array<std::string, 6>& texturePaths)
    {
        glGenTextures(1, &cubemapId);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapId);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < texturePaths.size(); i++)
        {
            stbi_set_flip_vertically_on_load(0);
            unsigned char* data = stbi_load(texturePaths[i].c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            }
            else
            {
                AL_ERROR("Cubemap texture failed to load at path: ", texturePaths[i]);
            }

            stbi_image_free(data);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

}