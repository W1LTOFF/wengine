#include "wengine/shader.hpp"
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

void Shader::compile(const char *vertexPath, const char *fragmentPath) {
    unsigned int vertex, fragment;
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    try {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    } catch (std::ifstream::failure e) {
        std::print("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {}\n", e.what());
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::print("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}\n", infoLog);
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::print("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}\n",
                   infoLog);
    }

    this->id = glCreateProgram();
    glAttachShader(this->id, vertex);
    glAttachShader(this->id, fragment);
    glLinkProgram(this->id);
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->id, 512, NULL, infoLog);
        std::print("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog);
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use() { glUseProgram(this->id); }

void Shader::setBool(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}

void Shader::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(this->id, name), value);
}
