#include "wengine/resourceManager.hpp"
#include "wengine/shader.hpp"
#include "wengine/texture.hpp"
#include <string>

void ResourceManager::loadShader(std::string name, const char *vertextPath, const char *fragmentPath, const char *geometryPath) {
    Shader shader;
    shader.compile(vertextPath, fragmentPath);
    ResourceManager::shaders[name] = shader;
}

void ResourceManager::loadTexture(std::string name, const char *texturePath) {
    Texture texture;
    texture.generate(texturePath);
    ResourceManager::textures[name] = texture;
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
