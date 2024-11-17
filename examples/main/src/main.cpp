#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"
#include "glm/matrix.hpp"
#include "glm/trigonometric.hpp"
#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

// #include "wengine/model.hpp"
#include "wengine/core/model.hpp"
#include "wengine/core/resourceManager.hpp"
#include "wengine/core/shader.hpp"

#include "wengine/core/camera.hpp"
#include "wengine/core/window.hpp"

// #include <gl/gl.h>

#include "wengine/gui/gui.hpp"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <print>
#include <system_error>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

#include "GLFW/glfw3.h"

// settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

// // camera
Camera camera;

float lastX = SCREEN_WIDTH / 2.0;
float lastY = SCREEN_HEIGHT / 2.0;

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

float xFromVertexToPixel(float x) { return (x + 1) * (SCREEN_WIDTH / 2.f); }
float yFromVertexToPixel(float y) { return (-y + 1) * (SCREEN_HEIGHT / 2.f); }
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        ResourceManager::loadShader("ourShader", "shader/vertex.shader", "shader/fragment.shader");
        ResourceManager::getShader("ourShader").use();
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS) {
        // glfwSetCursorPos(window, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        camera.mouseActive = false;
    } else {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        camera.mouseActive = true;
    }

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

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
    if (camera.firstMouse) {
        lastX = xPos;
        lastY = yPos;
        camera.firstMouse = false;
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

    // float vertices[] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //                     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //                     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //                     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //                     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //                     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //                     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //                     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //                     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    //                     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //                     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //                     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //                     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    //                     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //                     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //                     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //                     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //                     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //                     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //                     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    //                     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};
    float vertices[] = {
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f};
    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    if (!glfwInit()) {
        return -1;
    }

    Window window(SCREEN_WIDTH, SCREEN_HEIGHT, "wilt engine");
    window.makeContextCurrent();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD\n";
        return -1;
    }

    ResourceManager::loadShader("ourShader", "shader/vertex.shader", "shader/fragment.shader");
    ResourceManager::loadShader("uiShader", "shader/uiVertex.shader", "shader/uiFragment.shader");
    ResourceManager::loadShader("lightShader", "shader/vertex.shader", "shader/lightShaderFrag.shader");

    float ui[] = {-0.7f, -0.8f, 0.f, 0.f, 1.f, 0.7f, -1.f, 0.f, 1.f, 0.f,
                  -0.7f, -1.f, 0.f, 0.f, 0.f, -0.7f, -0.8f, 0.f, 0.f, 1.f,
                  0.7f, -0.8f, 0.f, 1.f, 1.f, 0.7f, -1.f, 0.f, 1.f, 0.f};
    unsigned int UI_VBO;
    glGenBuffers(1, &UI_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, UI_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ui), ui, GL_STATIC_DRAW);
    unsigned int UI_VAO;
    glGenVertexArrays(1, &UI_VAO);
    glBindVertexArray(UI_VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
                          (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

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

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
    //                       (void *)0);
    // glEnableVertexAttribArray(0);
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float),
    //                       (void *)(3 * sizeof(float)));
    // glEnableVertexAttribArray(1);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glm::vec3 lightPos = {2.f, 1.f, -2.f};

    ResourceManager::loadTexture("texture", "./res/texture/notexture.png", true);
    ResourceManager::loadTexture("uiTexture", "./res/texture/texture.png", true);

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glEnable(GL_DEPTH_TEST);

    glfwSetInputMode(window.getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window.getWindow(), mouse_callback);
    glfwSetScrollCallback(window.getWindow(), scrollCallback);

    Gui gui(window.getWindow());

    // int frames = 0;
    // double lastTime = glfwGetTime();

    camera.position = {1, 1, 3};

    while (!window.windowShouldClose()) {
        double currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // if (currentFrame - lastTime >= 1.f) {
        //     std::print("frames:      {}\n", frames);
        //     std::print("1/deltaTime: {}\n", 1 / deltaTime);
        //     frames = 0;
        //     lastTime = currentFrame;
        // }
        // frames++;

        processInput(window.getWindow());
        window.handleInput();
        window.update();

        glClearColor(0.f, 0.2f, 0.2f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture("texture").id);

        ResourceManager::getShader("ourShader").use();
        ResourceManager::getShader("ourShader").setVec3f("lightColor", {1.f, 1.f, 1.f});
        ResourceManager::getShader("ourShader").setVec3f("lightPos", lightPos);
        ResourceManager::getShader("ourShader").setVec3f("cameraPos", camera.position);

        glm::mat4 model = glm::mat4(1.f);
        glm::mat4 normalMat = glm::transpose(glm::inverse(model));
        ResourceManager::getShader("ourShader").setMat4("normalMat", normalMat);

        glm::mat4 view = camera.getViewMatrix();

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.fov),
            (float)window.width / (float)window.height, 0.1f, 100.f);

        ResourceManager::getShader("ourShader").setMat4("model", model);
        ResourceManager::getShader("ourShader").setMat4("view", view);
        ResourceManager::getShader("ourShader").setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        model = glm::mat4(1.f);
        lightPos = glm::rotate(model, (float)glm::radians(90 * deltaTime), {0.f, 1.f, 0.f}) * glm::vec4(lightPos, 1.f);

        ResourceManager::getShader("lightShader").use();
        ResourceManager::getShader("lightShader").setMat4("view", view);
        ResourceManager::getShader("lightShader").setMat4("model", glm::translate(model, lightPos));
        ResourceManager::getShader("lightShader").setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 6 * 6);

        ResourceManager::getShader("uiShader").use();

        glBindTexture(GL_TEXTURE_2D, ResourceManager::getTexture("uiTexture").id);

        glBindVertexArray(UI_VAO);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        gui.render(&window, &camera);

        window.swapBuffers();

        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteBuffers(1, &EBO);
    glfwTerminate();
    return 0;
}
