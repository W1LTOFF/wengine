#ifndef GUI_HPP
#define GUI_HPP

#include <GLFW/glfw3.h>
#include <camera.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class Gui {
  private:
  public:
    Gui(GLFWwindow *window);
    void render(GLFWwindow *window, Camera *camera);
    void debug(GLFWwindow *window, Camera *camera);
};

#endif
