#ifndef WENGINE_MODEL
#define WENGINE_MODEL

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include "wengine/core/shader.hpp"
#include "wengine/core/texture.hpp"
#include <glad/glad.h>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 textureCoords;
};

class Mesh {
  public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void draw(Shader &shader);

  private:
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};

#endif
