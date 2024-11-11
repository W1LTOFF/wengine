#include "wengine/core/window.hpp"
#include "GLFW/glfw3.h"
#include <gl/gl.h>
#include <print>

Window::Window(int width, int height, const char *title) {
    this->width = width;
    this->height = height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (this->window == NULL) {
        std::print("Failed to initialize window\n");
        glfwTerminate();
    }
    glfwSetFramebufferSizeCallback(
        this->window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });
}

void Window::makeContextCurrent() { glfwMakeContextCurrent(this->window); }

bool Window::windowShouldClose() { return glfwWindowShouldClose(this->window); }

void Window::swapBuffers() { glfwSwapBuffers(this->window); }

void Window::handleInput() {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }
}

void Window::update() {
    glfwGetWindowSize(this->window, &this->width, &this->height);
}

// DELETE
GLFWwindow *Window::getWindow() { return this->window; }
