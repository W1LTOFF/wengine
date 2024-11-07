#ifndef WENGINE_MODEL
#define WENGINE_MODEL

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <glad/glad.h>
#include <vector>

struct Vertice {
    glm::vec3 position;
    // glm::vec3 normal;
    glm::vec2 texturePos;
};

class Model {
  private:
  public:
    // unsigned int *indeces;
    std::vector<Vertice> vertices;

    // Model();
    void draw(int primitive = GL_TRIANGLES);
};

#endif
