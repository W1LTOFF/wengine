#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

#include <fstream>
#include <print>
#include <string>

class Shader {
  private:
  public:
    unsigned int id;

    Shader(const char *vertexPath, const char *fragmentPath);
    void use();
    void setBool(const char *name, bool value);
    void setInt(const char *name, int value);
    void setFloat(const char *name, float value);
};

#endif
