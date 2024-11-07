#include "wengine/model.hpp"

void Model::draw(int primitive) {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
