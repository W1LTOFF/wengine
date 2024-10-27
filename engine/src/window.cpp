#include "window.hpp"
#include <print>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

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
}

void Window::MakeContextCurrent() { glfwMakeContextCurrent(this->window); }

void Window::framebufferSizeCallback() {
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);
}

bool Window::windowShouldClose() { return glfwWindowShouldClose(this->window); }

void Window::swapBuffers() { glfwSwapBuffers(this->window); }
