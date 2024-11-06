#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

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
};
#endif
