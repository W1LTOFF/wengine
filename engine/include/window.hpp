#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
// #include <glad/glad.h>

class Window {
  private:
    GLFWwindow *window;
    int width;
    int height;
    void framebufferSizeCallback();

  public:
    Window(int width, int height, const char *title);
    void MakeContextCurrent();
    bool windowShouldClose();
    void swapBuffers();
    void handleInput();
};

#endif
