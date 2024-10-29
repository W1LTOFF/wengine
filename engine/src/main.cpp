#include <chrono>
#include <filesystem>
#include <functional>
#include <thread>

#include "glm/detail/qualifier.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"

#include "camera.hpp"
#include "glm/ext/quaternion_geometric.hpp"
#include "glm/trigonometric.hpp"
#include "shader.hpp"
#include "window.hpp"

#include <GLFW/glfw3.h>
#include <gl/gl.h>

#include <glad/glad.h>
#include <iostream>
#include <print>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// // camera
// glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
// glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
// glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
Camera camera;

bool firstMouse = true;
// float yaw = -90.0f;
// float pitch = 0.0f;
float lastX = SCREEN_WIDTH / 2.0;
float lastY = SCREEN_HEIGHT / 2.0;
// float fov = 45.0f;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.processKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.processKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.processKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.processKeyboard(RIGHT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        camera.processKeyboard(UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
        camera.processKeyboard(DOWN, deltaTime);
    }
}

void mouse_callback(GLFWwindow *window, double xPos, double yPos) {
    // if (firstMouse) {
    //     lastX = xpos;
    //     lastY = ypos;
    //     firstMouse = false;
    // }
    //
    // float xoffset = xpos - lastX;
    // float yoffset = lastY - ypos;
    // lastX = xpos;
    // lastY = ypos;
    //
    // float sensitivity = 0.1f;
    // xoffset *= sensitivity;
    // yoffset *= sensitivity;
    //
    // yaw += xoffset;
    // pitch += yoffset;
    //
    // if (pitch > 89.0f)
    //     pitch = 89.0f;
    // if (pitch < -89.0f)
    //     pitch = -89.0f;
    //
    // glm::vec3 direction;
    // direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    // direction.y = sin(glm::radians(pitch));
    // direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    // cameraFront = glm::normalize(direction);

    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }

    float dx = xPos - lastX;
    float dy = lastY - yPos;

    lastX = xPos;
    lastY = yPos;

    camera.processMouseMovement(dx, dy);
}

void scrollCallback(GLFWwindow *window, double dx, double dy) {
    camera.processMouseScroll(dy);
}

int main(int argc, char **argv) {

    float lastX = SCREEN_WIDTH / 2.f, lastY = SCREEN_HEIGHT / 2.f;

    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 0.0f,
        0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 1.0f, -0.5f, -0.5f, 0.5f,  0.0f, 0.0f,

        -0.5f, 0.5f,  0.5f,  1.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 0.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  0.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.5f,  -0.5f, -0.5f, 1.0f, 1.0f,
        0.5f,  -0.5f, 0.5f,  1.0f, 0.0f, 0.5f,  -0.5f, 0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

        -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, 0.5f,  0.5f,  -0.5f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, 0.5f,  0.5f,  0.0f, 0.0f, -0.5f, 0.5f,  -0.5f, 0.0f, 1.0f};

    // float vertices[] = {
    //     // positions          // colors           // texture coords
    //     0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
    //     0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
    //     -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    // };

    // float vertices[] = {
    //     // positions // colors
    //     0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
    //     -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
    //     0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f, // top
    // };

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
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    if (!glfwInit()) {
        return -1;
    }

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "wilt engine");
    window.MakeContextCurrent();
    window.MakeContextCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    Shader ourShader("shader/vertex.shader", "shader/fragment.shader");

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data =
        stbi_load(std::filesystem::absolute("./res/texture/notexture.png")
                      .string()
                      .c_str(),
                  &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::print("Failed to load texture");
    }
    stbi_image_free(data);

    ourShader.use();

    ourShader.setInt("ourTexture", 0);

    // glm::mat4 trans = glm::mat4(1.0f);
    // trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0,
    // 0.0, 1.0)); trans = glm::scale(trans, glm::vec3(1, 1, 1));
    //
    // unsigned int transformLoc = glGetUniformLocation(ourShader.id,
    // "transform"); glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
    // glm::value_ptr(trans));

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
    glfwSetScrollCallback(window.getWindow(), scrollCallback);

    while (!window.windowShouldClose()) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // glm::vec3 direction;
        // direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        // direction.y = sin(glm::radians(pitch));
        // direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

        window.handleInput();
        processInput(window.getWindow());
        const float cameraSpeed = 2.5f * deltaTime;
        //
        // if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS)
        //     cameraPos += cameraSpeed * direction;
        // if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS)
        //     cameraPos -= cameraSpeed * direction;
        // if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS)
        //     cameraPos -=
        //         glm::normalize(glm::cross(direction, cameraUp)) *
        //         cameraSpeed;
        // if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS)
        //     cameraPos +=
        //         glm::normalize(glm::cross(direction, cameraUp)) *
        //         cameraSpeed;

        glClearColor(0.f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

        ourShader.use();

        glm::mat4 model = glm::mat4(1.f);

        model = glm::scale(model, {0.5f, 0.5f, 0.5f});

        // model =
        //     glm::rotate(model, (float)glfwGetTime(),
        //     glm::vec3(1.0, 1.0, 1.0));

        // glm::mat4 view = glm::mat4(1.f);
        glm::mat4 view = camera.getViewMatrix();

        // view = glm::lookAt(cameraPos, cameraPos + direction, cameraUp);

        // glm::mat4 projection = glm::mat4(1.f);
        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fov),
            (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.f);

        glUniformMatrix4fv(glGetUniformLocation(ourShader.id, "model"), 1,
                           GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.id, "view"), 1,
                           GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(ourShader.id, "projection"), 1,
                           GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.swapBuffers();

        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
