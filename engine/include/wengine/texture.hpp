#ifndef WENGINE_TEXTURE
#define WENGINE_TEXTURE

#include <filesystem>
#include <glad/glad.h>
#include <print>

class Texture {
  private:
    unsigned int id;

  public:
    void generate(const char *path);
    unsigned int getId();
};

#endif
