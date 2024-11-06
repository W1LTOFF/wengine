#ifndef WENGINE_TEXTURE
#define WENGINE_TEXTURE

#include <filesystem>
#include <glad/glad.h>
#include <print>

class Texture {
  public:
    unsigned int id;

    unsigned int width, height;
    unsigned int internalFormat;
    unsigned int imageFormat;

    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;

    void generate(unsigned int width, unsigned int height, unsigned char *data);
    Texture();
    void bind();
};

#endif
