#include "window.hpp"
#include "GLFW/glfw3.h"
#include <gl/gl.h>
#include <print>

Window::Window(int width, int height, const char *title) {
    this->width = width;
    this->height = height;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    this->window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (this->window == NULL) {
        std::print("Failed to initialize window\n");
        glfwTerminate();
    }
    this->framebufferSizeCallback();
}

void Window::MakeContextCurrent() { glfwMakeContextCurrent(this->window); }

void Window::framebufferSizeCallback() {
    glfwSetFramebufferSizeCallback(
        this->window, [](GLFWwindow *window, int width, int height) {
            glViewport(0, 0, width, height);
        });
}

bool Window::windowShouldClose() { return glfwWindowShouldClose(this->window); }

void Window::swapBuffers() { glfwSwapBuffers(this->window); }

void Window::handleInput() {
    if (glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(this->window, true);
    }
}

// DELETE
GLFWwindow *Window::getWindow() { return this->window; }
