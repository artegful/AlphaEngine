#include "Model.h"

#include "Core/Log.h"
#include <filesystem>
#include "GL/glew.h"

namespace Alpha
{
    std::shared_ptr<Model> Model::Create(const std::string& path)
    {
        return std::make_shared<Model>(path);
    }


    Model::Model(string const& path) : path(path)
    {
        glGenBuffers(1, &instanceTransformsBuffer);

        LoadModel(path);
    }

    void Model::Draw(Shader& shader, std::vector<glm::mat4>& transforms)
    {
        glBindBuffer(GL_ARRAY_BUFFER, instanceTransformsBuffer);
        glBufferData(GL_ARRAY_BUFFER, transforms.size() * sizeof(glm::mat4), transforms.data(), GL_DYNAMIC_DRAW);

        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw(shader, transforms.size());
        }
    }

    void Model::LoadModel(string const& path)
    {
        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
       
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            AL_ERROR("ASSIMP: ", importer.GetErrorString());
            return;
        }

        directory = std::filesystem::path(path).parent_path();

        HandleNode(scene->mRootNode, scene);
    }

    void Model::HandleNode(aiNode* node, const aiScene* scene)
    {
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(HandleMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            HandleNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::HandleMesh(aiMesh* mesh, const aiScene* scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<std::shared_ptr<Texture>> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;
            
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
            {
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);
            }

            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        aiMaterial* modelMaterial = scene->mMaterials[mesh->mMaterialIndex];
        Material material;

        vector<std::shared_ptr<Texture>> diffuseMaps = LoadMaterialTextures(modelMaterial, aiTextureType_DIFFUSE, "texture_diffuse");
        vector<std::shared_ptr<Texture>> specularMaps = LoadMaterialTextures(modelMaterial, aiTextureType_SPECULAR, "texture_specular");
        std::vector<std::shared_ptr<Texture>> normalMaps = LoadMaterialTextures(modelMaterial, aiTextureType_HEIGHT, "texture_normal");
        std::vector<std::shared_ptr<Texture>> heightMaps = LoadMaterialTextures(modelMaterial, aiTextureType_AMBIENT, "texture_height");

        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

        aiColor3D color(1.0f, 1.0f, 1.0f);
        if (modelMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
        {
            material.DiffuseColor = glm::vec3(color.r, color.g, color.b);
        }

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

        return Mesh(std::move(vertices), std::move(indices), std::move(material), instanceTransformsBuffer);
    }

    vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
    {
        vector<std::shared_ptr<Texture>> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString textureString;
            mat->GetTexture(type, i, &textureString);
            std::string fullPath = (directory / textureString.C_Str()).string();

            bool skip = false;
            for (unsigned int j = 0; j < loadedTextures.size(); j++)
            {
                if (loadedTextures[j]->GetPath() == fullPath)
                {
                    textures.push_back(loadedTextures[j]);
                    skip = true;
                    break;
                }
            }
            if (!skip)
            {
                std::shared_ptr<Texture> texture = Texture::Create(fullPath);
                texture->SetType(typeName);
                loadedTextures.push_back(texture);
                textures.push_back(texture);
            }
        }
        return textures;
    }
}