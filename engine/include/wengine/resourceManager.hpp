#ifndef WENGINE_RESOURCEMANAGER
#define WENGINE_RESOURCEMANAGER

#include "wengine/shader.hpp"
#include <filesystem>
#include <glad/glad.h>
#include <map>
#include <print>

namespace wilt {
class Texture {
  private:
    unsigned int id;

  public:
    Texture(const char *path);
    unsigned int getId();
};

class ResourceManager {
  private:
    std::map<const char *, Shader> shaders;
    std::map<const char *, wilt::Texture> textures;

  public:
    ResourceManager();

    Shader getShader(const char *name);
    wilt::Texture getTexture(const char *name);

    void newShader(const char *name, const char *vertextPath,
                   const char *fragmentPath, const char *geometryPath = NULL);
    void newTexture(const char *name, const char *texturePath);

    void wipeAll();
};
} // namespace wilt

#endif
