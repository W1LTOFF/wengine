#include "wengine/core/model.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/trigonometric.hpp"
#include "wengine/core/shader.hpp"
#include <cstddef>
#include <gl/gl.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);

    glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), &this->vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int), &this->indices[0], GL_STATIC_DRAW);

    // Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(Vertex), (void *)0);
    // Normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, normal));
    // Textures
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, sizeof(Vertex), (void *)offsetof(Vertex, textureCoords));

    glBindVertexArray(0);
}

void Mesh::draw(Shader &shader) {
    shader.use();
    shader.setVec3f("lightColor", {1.f, 1.f, 1.f});
    shader.setVec3f("lightPos", {2.f, 1.f, -2.f});
    shader.setVec3f("cameraPos", {1, 1, 3});

    glm::mat4 model = glm::mat4(1.f);
    glm::mat4 normalMat = glm::transpose(glm::inverse(model));
    shader.setMat4("normalMat", normalMat);

    glm::mat4 view = glm::mat4(1.f);

    glm::mat4 projection = glm::perspective(
        glm::radians(90.f),
        (float)1280 / (float)720, 0.1f, 100.f);

    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);

    glBindVertexArray(this->VAO);
    this->textures.front().bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}
