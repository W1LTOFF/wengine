#ifndef WENGINE_RESOURCEMANAGER
#define WENGINE_RESOURCEMANAGER

#include "wengine/shader.hpp"
#include "wengine/texture.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <map>
#include <print>
#include <string>

// namespace wilt {
// class ResourceManager {
// };

class ResourceManager {
  private:
    ResourceManager();

    static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile, const char *gShaderFile);
    static Texture loadTextureFromFile(const char *file, bool alpha);

  public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

    static Shader getShader(std::string name);
    static Texture getTexture(std::string name);

    static Shader loadShader(std::string name, const char *vertextPath, const char *fragmentPath, const char *geometryPath = NULL);
    static Texture loadTexture(std::string name, const char *texturePath, bool alpha);

    static void clear();
};
// } // namespace wilt

#endif
