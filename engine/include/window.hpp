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
    // delete window getter later, dont need it in release
    // TODO: wrap all window related stuff
    GLFWwindow *getWindow();
    Window(int width, int height, const char *title);
    void MakeContextCurrent();
    bool windowShouldClose();
    void swapBuffers();
    void handleInput();
};

#endif
