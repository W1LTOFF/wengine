#ifndef WENGINE_MODEL
#define WENGINE_MODEL

#include "glm/ext/vector_float2.hpp"
#include "glm/ext/vector_float3.hpp"
#include <vector>

namespace wilt {

struct Vertice {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texturePos;
};

class Model {
  private:
    std::vector<Vertice> vertices;

  public:
    // void
};

} // namespace wilt

#endif
