#include "wengine/core/texture.hpp"

// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

Texture::Texture() : width(0), height(0), internalFormat(GL_RGBA), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_NEAREST), filterMax(GL_NEAREST) {
    glGenTextures(1, &this->id);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->width = width;
    this->height = height;
    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    // set the texture wrapping/filtering options (on currently boun texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);
    // load and generate the texture
    // unsigned int width, height, nrChannels;
    // stbi_set_flip_vertically_on_load(true);
    // unsigned char *data =
    //     stbi_load(std::filesystem::absolute(path).string().c_str(), &width,
    //               &height, &nrChannels, 0);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // stbi_image_free(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->id);
}
