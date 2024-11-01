#include "wengine/gui.hpp"
#include "GLFW/glfw3.h"
#include "glm/ext/vector_float2.hpp"
#include "imgui.h"

Gui::Gui(GLFWwindow *window) {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

void Gui::debug(Window *window, Camera *camera) {
    ImGui::Begin("camera");
    ImGui::Text("x %.3f", camera->position.x);
    ImGui::InputFloat3("position", &camera->position.x);
    ImGui::InputFloat2("yaw pitch", &camera->yaw);
    // ImGui::Text("x: %f", camera->position.x);
    // ImGui::Text("y: %f", camera->position.y);
    // ImGui::Text("z: %f", camera->position.z);
    ImGui::SliderFloat("fov", &camera->fov, 10.0f, 180.0f);
    ImGui::InputFloat("movementSpeed", &camera->movementSpeed);
    ImGui::InputFloat("mouseSensitivity", &camera->mouseSensitivity);
    ImGui::Text("mouseActive %i", camera->mouseActive);
    ImGui::Text("firstMouse %i", camera->firstMouse);

    ImGui::Text("front %.3f %.3f %.3f", camera->front.x, camera->front.y,
                camera->front.z);
    ImGui::Text("up %.3f %.3f %.3f", camera->up.x, camera->up.y, camera->up.z);
    ImGui::Text("right %.3f %.3f %.3f", camera->right.x, camera->right.y,
                camera->right.z);
    const char *xD, *zD;
    if (camera->front.x > 0) {
        xD = "x+";
    } else {
        xD = "x-";
    }
    if (camera->right.x < 0) {
        zD = "z+";
    } else {
        zD = "z-";
    }
    ImGui::Text("%s %s", xD, zD);
    ImGui::Text("worldUp %.3f %.3f %.3f", camera->worldUp.x, camera->worldUp.y,
                camera->worldUp.z);
    ImGui::End();

    ImGui::Begin("window");
    double xPos, yPos;
    glfwGetCursorPos(window->getWindow(), &xPos, &yPos);
    ImGui::Text("mousePosition x:%.3f y:%.3f", xPos, yPos);
    ImGui::Text("width %i height %i", window->width, window->height);
    ImGui::End();
}

void Gui::render(Window *window, Camera *camera) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    debug(window, camera);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
