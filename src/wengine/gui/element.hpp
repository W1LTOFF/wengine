#ifndef WENGINE_ELEMENT
#define WENGINE_ELEMENT

#include "glm/ext/vector_float2.hpp"
#include "wengine/core/model.hpp"
#include <vector>

class Element {
  private:
  public:
    glm::vec2 relativePos;
    glm::vec2 pos;

    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    void setRelativePos(float x, float y);
    void setPos(float x, float y);

    glm::vec2 getRelativePos();
    glm::vec2 getPos();

    void updateRelativePos();
    void updatePos();
};

#endif
