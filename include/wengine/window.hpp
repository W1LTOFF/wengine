#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
// #include <glad/glad.h>

class Window {
  private:
    GLFWwindow *window;

  public:
    int width;
    int height;

    // delete window getter later, dont need
    // it in release
    // TODO: wrap all window related stuff
    GLFWwindow *getWindow();
    Window(int width, int height, const char *title);
    void update();
    void makeContextCurrent();
    bool windowShouldClose();
    void swapBuffers();
    void handleInput();
};

#endif
