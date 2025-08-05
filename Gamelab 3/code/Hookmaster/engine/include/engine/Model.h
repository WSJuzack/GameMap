#include <iostream>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Shader.h"
#include "engine/Mesh.h"

namespace gl3
{
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

    class Model
    {
    public:
        Model(const std::string& path);
        void Draw(Shader &shader);

        std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
        std::vector<Mesh> meshes;
        std::string directory;
        bool gammaCorrection;
    private:
        void loadModel(std::string path);
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                             std::string typeName);
    };
}

