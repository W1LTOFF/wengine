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
void Shader::setVec2f(const char *name, const glm::vec2 &value) {
    glUniform2f(glGetUniformLocation(this->id, name), value.x, value.y);
}
void Shader::setVec3f(const char *name, const glm::vec3 &value) {
    glUniform3f(glGetUniformLocation(this->id, name), value.x, value.y, value.z);
}
void Shader::setVec4f(const char *name, const glm::vec4 &value) {
    glUniform4f(glGetUniformLocation(this->id, name), value.x, value.y, value.z, value.w);
}
void Shader::setMat4(const char *name, const glm::mat4 &value) {
    glUniformMatrix4fv(glGetUniformLocation(this->id, name), 1, false, glm::value_ptr(value));
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
