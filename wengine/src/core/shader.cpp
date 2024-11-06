#include "wengine/shader.hpp"
#include <fstream>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

void Shader::compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    unsigned int vShader, fShader, gShader;

    // vertex Shader
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, &vertexSource, NULL);
    glCompileShader(vShader);
    checkCompileErrors(vShader, "VERTEX");
    // fragment Shader
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, &fragmentSource, NULL);
    glCompileShader(fShader);
    checkCompileErrors(fShader, "FRAGMENT");
    // if geometry shader source code is given, also compile geometry shader
    if (geometrySource != NULL) {
        gShader = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gShader, 1, &geometrySource, NULL);
        glCompileShader(gShader);
        checkCompileErrors(gShader, "GEOMETRY");
    }
    // shader program
    this->id = glCreateProgram();
    glAttachShader(this->id, vShader);
    glAttachShader(this->id, fShader);
    if (geometrySource != NULL) {
        glAttachShader(this->id, gShader);
    }
    glLinkProgram(this->id);
    checkCompileErrors(this->id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vShader);
    glDeleteShader(fShader);
    if (geometrySource != NULL) {
        glDeleteShader(gShader);
    }
    // unsigned int vertex, fragment;
    // std::string vertexCode;
    // std::string fragmentCode;
    // std::ifstream vShaderFile;
    // std::ifstream fShaderFile;
    // try {
    //     vShaderFile.open(vertexPath);
    //     fShaderFile.open(fragmentPath);
    //
    //     std::stringstream vShaderStream, fShaderStream;
    //
    //     vShaderStream << vShaderFile.rdbuf();
    //     fShaderStream << fShaderFile.rdbuf();
    //
    //     vShaderFile.close();
    //     fShaderFile.close();
    //
    //     vertexCode = vShaderStream.str();
    //     fragmentCode = fShaderStream.str();
    // } catch (std::ifstream::failure e) {
    //     std::print("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: {}\n", e.what());
    // }
    //
    // const char *vShaderCode = vertexCode.c_str();
    // const char *fShaderCode = fragmentCode.c_str();
    //
    // int success;
    // char infoLog[512];
    //
    // vertex = glCreateShader(GL_VERTEX_SHADER);
    // glShaderSource(vertex, 1, &vShaderCode, NULL);
    // glCompileShader(vertex);
    // glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    //     std::print("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}\n", infoLog);
    // }
    //
    // fragment = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(fragment, 1, &fShaderCode, NULL);
    // glCompileShader(fragment);
    // glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    // if (!success) {
    //     glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    //     std::print("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}\n",
    //                infoLog);
    // }
    //
    // this->id = glCreateProgram();
    // glAttachShader(this->id, vertex);
    // glAttachShader(this->id, fragment);
    // glLinkProgram(this->id);
    // glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    // if (!success) {
    //     glGetProgramInfoLog(this->id, 512, NULL, infoLog);
    //     std::print("ERROR::SHADER::PROGRAM::LINKING_FAILED\n{}\n", infoLog);
    // }
    //
    // glDeleteShader(vertex);
    // glDeleteShader(fragment);
}

Shader &Shader::use() {
    glUseProgram(this->id);
    return *this;
}

void Shader::setBool(const char *name, bool value) {
    glUniform1i(glGetUniformLocation(this->id, name), (int)value);
}

void Shader::setInt(const char *name, int value) {
    glUniform1i(glGetUniformLocation(this->id, name), value);
}

void Shader::setFloat(const char *name, float value) {
    glUniform1f(glGetUniformLocation(this->id, name), value);
}

void Shader::checkCompileErrors(unsigned int object, std::string type) {
    int success;
    char infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::print("| ERROR::SHADER: Compile-time error: Type: {}\n{}\n -- --------------------------------------------------- -- ", type, infoLog);
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, infoLog);
            std::print("| ERROR::Shader: Link-time error: Type: {}\n{}\n -- --------------------------------------------------- -- ", type, infoLog);
        }
    }
}
