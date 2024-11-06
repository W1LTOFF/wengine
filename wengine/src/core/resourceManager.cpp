#include "wengine/resourceManager.hpp"
#include "wengine/shader.hpp"
#include "wengine/texture.hpp"
#include <filesystem>
#include <fstream>
#include <string>
#include <strstream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

std::map<std::string, Texture> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::loadShaderFromFile(const char *vPath, const char *fPath, const char *gPath) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    try {
        std::ifstream vShaderFile(vPath);
        std::ifstream fShaderFile(fPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        if (gPath != NULL) {
            std::ifstream gShaderFile(gPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    } catch (std::ifstream::failure e) {
        std::print("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {}\n", e.what());
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    const char *gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gPath != NULL ? gShaderCode : NULL);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha) {
    Texture texture;

    stbi_set_flip_vertically_on_load(true);

    if (alpha) {
        texture.internalFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }

    int width, height, nrChannels;
    unsigned char *data = stbi_load(std::filesystem::absolute(file).string().c_str(), &width, &height, &nrChannels, 0);

    texture.generate(width, height, data);

    stbi_image_free(data);
    return texture;
}

Shader ResourceManager::loadShader(std::string name, const char *vertextPath, const char *fragmentPath, const char *geometryPath) {
    ResourceManager::shaders[name] = ResourceManager::loadShaderFromFile(vertextPath, fragmentPath, geometryPath);
    return ResourceManager::shaders[name];
}

Texture ResourceManager::loadTexture(std::string name, const char *texturePath, bool alpha) {
    ResourceManager::textures[name] = ResourceManager::loadTextureFromFile(texturePath, alpha);
    return ResourceManager::textures[name];
}

Shader ResourceManager::getShader(std::string name) {
    return ResourceManager::shaders[name];
}

Texture ResourceManager::getTexture(std::string name) {
    return ResourceManager::textures[name];
}

// void wilt::ResourceManager::newShader(const char *name, const char *vertextPath,
//                                       const char *fragmentPath,
//                                       const char *geometryPath) {
//     this->shaders[name] = Shader(vertextPath, fragmentPath);
// }
//
// void wilt::ResourceManager::newTexture(const char *name,
//                                        const char *texturePath) {
//     this->textures[name] = Texture(texturePath);
// }
//
// Shader wilt::ResourceManager::getShader(const char *name) {
//     return this->shaders[name];
// }
//
// wilt::Texture wilt::ResourceManager::getTexture(const char *name) {
//     return this->textures[name];
// }
