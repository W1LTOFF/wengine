#include "wengine/resourceManager.hpp"
#include "wengine/shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

wilt::Texture::Texture(const char *path) {
    glGenTextures(1, &this->id);
    glBindTexture(GL_TEXTURE_2D, this->id);
    // set the texture wrapping/filtering options (on currently bound
    // texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(std::filesystem::absolute(path).string().c_str(), &width,
                  &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::print("Failed to load texture");
    }
    stbi_image_free(data);
}

unsigned int wilt::Texture::getId() { return this->id; }

void wilt::ResourceManager::newShader(const char *name, const char *vertextPath,
                                      const char *fragmentPath,
                                      const char *geometryPath) {
    this->shaders[name] = Shader(vertextPath, fragmentPath);
}

void wilt::ResourceManager::newTexture(const char *name,
                                       const char *texturePath) {
    this->textures[name] = Texture(texturePath);
}

Shader wilt::ResourceManager::getShader(const char *name) {
    return this->shaders[name];
}

wilt::Texture wilt::ResourceManager::getTexture(const char *name) {
    return this->textures[name];
}
