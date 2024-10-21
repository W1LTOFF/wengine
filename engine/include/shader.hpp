#ifndef SHADER_HPP
#define SHADER_HPP

#include "glad/glad.h"
#include <fstream>
#include <string>

std::string readToString(const char *path);
unsigned int shaderCompile(const char *vertexShaderPath,
                           const char *fragmentShaderPath);

#endif
