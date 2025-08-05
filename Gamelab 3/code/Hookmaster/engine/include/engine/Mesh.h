#pragma once
#include <iostream>
#include "glm/glm.hpp"
#include "tiny_gltf/tiny_gltf.h"
#include "Mesh.h"
#include "Shader.h"


namespace gl3
{
    struct Vertex {
        // position
        glm::vec3 Position;
        // normal
        glm::vec3 Normal;
        // texCoords
        glm::vec2 TexCoords;
        // tangent
        glm::vec3 Tangent;
        // bitangent
        glm::vec3 Bitangent;
    };

    struct Texture {
        unsigned int id;
        std::string type;
        std::string path;
    };
    class Mesh {

    public:
        // mesh data
        std::vector<Vertex>       vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture>      textures;

        Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
        void Draw(Shader &shader);
    private:
        //  render data
        unsigned int VAO, VBO, EBO;

        void setupMesh();

    };
}