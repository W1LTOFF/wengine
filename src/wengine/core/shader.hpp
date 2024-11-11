#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/matrix.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <fstream>
#include <print>
#include <string>

class Shader {
  private:
    void checkCompileErrors(unsigned int object, std::string type);

  public:
    unsigned int id;

    Shader &use();
    void compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource);

    void setBool(const char *name, bool value);
    void setInt(const char *name, int value);
    void setFloat(const char *name, float value);
    void setVec2f(const char *name, const glm::vec2 &value);
    void setVec3f(const char *name, const glm::vec3 &value);
    void setVec4f(const char *name, const glm::vec4 &value);
    void setMat4(const char *name, const glm::mat4 &value);
};
#endif
