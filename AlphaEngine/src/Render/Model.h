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

        vector<std::shared_ptr<Texture>> TexturesLoaded;
        vector<Mesh> Meshes;
        std::filesystem::path Directory;

        Model(string const& path);

        void Draw(Shader& shader);

    private:
        // loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
        void loadModel(string const& path);

        void processNode(aiNode* node, const aiScene* scene);
        Mesh processMesh(aiMesh* mesh, const aiScene* scene);
        vector<std::shared_ptr<Texture>> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
    };
}