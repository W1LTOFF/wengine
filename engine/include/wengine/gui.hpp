#ifndef GUI_HPP
#define GUI_HPP

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <wengine/camera.hpp>
#include <wengine/window.hpp>

class Gui {
  private:
  public:
    Gui(GLFWwindow *window);
    void render(Window *window, Camera *camera);
    void debug(Window *window, Camera *camera);
};

#endif
