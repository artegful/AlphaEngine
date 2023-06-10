#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
#include <filesystem>

namespace Alpha
{
    using namespace std;

    class Model
    {
    public:
        static std::shared_ptr<Model> Create(const std::string& path);

        Model(string const& path);

        void Draw(Shader& shader, std::vector<glm::mat4>& transforms);
        std::string GetPath() const { return path; }

    private:
        unsigned int instanceTransformsBuffer;
        vector<std::shared_ptr<Texture>> loadedTextures;
        vector<Mesh> meshes;
        std::filesystem::path directory;
        std::string path;

        void LoadModel(string const& path);
        void HandleNode(aiNode* node, const aiScene* scene);
        Mesh HandleMesh(aiMesh* mesh, const aiScene* scene);
        vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    };
}