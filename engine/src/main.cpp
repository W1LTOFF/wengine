#include <glad/glad.h>

#include "shader.hpp"
#include "window.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char **argv) {

    // float vertices[] = {
    //     // positions // colors // texture coords
    //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    //     0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    // };

    float vertices[] = {
        // positions // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top
    };

    // float texCoords[] = {
    //     0.0f, 0.0f, // lower-left corner
    //     1.0f, 0.0f, // lower-right corner
    //     0.5f, 1.0f  // top-center corner
    // };

    // float vertices[] = {
    //     0.5f,  0.5f,  0.0f, // top right
    //     0.5f,  -0.5f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, // bottom left
    //     -0.5f, 0.5f,  0.0f  // top left
    // };
    // unsigned int indices[] = {
    //     // note that we start from 0!
    //     0, 1, 3, // first triangle
    //     1, 2, 3  // second triangle
    // };

    if (!glfwInit()) {
        return -1;
    }

    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "wilt engine");
    window.MakeContextCurrent();
    window.MakeContextCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // unsigned int EBO;
    // glGenBuffers(1, &EBO);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
    //              GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float),
    //                       (void *)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    Shader ourShader("shader/vertex.shader", "shader/fragment.shader");

    // unsigned int texture;
    // glGenTextures(1, &texture);
    // glBindTexture(GL_TEXTURE_2D, texture);
    // // set the texture wrapping/filtering options (on currently bound
    // texture) glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // // load and generate the texture
    // int width, height, nrChannels;
    // unsigned char *data =
    //     stbi_load("NOT WORK IDK why", &width, &height, &nrChannels, 0);
    // if (data) {
    //     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
    //                  GL_UNSIGNED_BYTE, data);
    //     glGenerateMipmap(GL_TEXTURE_2D);
    // } else {
    //     std::cout << "Failed to load texture" << std::endl;
    // }
    // stbi_image_free(data);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    while (!window.windowShouldClose()) {
        // if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        //     glfwSetWindowShouldClose(window, true);
        // }
        glClearColor(0.f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glBindTexture(GL_TEXTURE_2D, texture);
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(VAO);
        ourShader.use();

        glDrawArrays(GL_TRIANGLES, 0, 3);
        window.swapBuffers();

        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
