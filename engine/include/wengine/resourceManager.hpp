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

  public:
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture> textures;

    static Shader getShader(std::string name);
    static Texture getTexture(std::string name);

    static void loadShader(std::string name, const char *vertextPath, const char *fragmentPath, const char *geometryPath = NULL);
    static void loadTexture(std::string name, const char *texturePath);

    static void clear();
};
// } // namespace wilt

#endif
