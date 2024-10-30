#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "glm/ext/matrix_transform.hpp"
#include <glm/glm.hpp>

enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN };

const float YAW = -90.f;
const float PITCH = 0.f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.f;

class Camera {
  private:
    void updateCameraVectors();

  public:
    bool mouseActive = true;
    glm::vec3 position;
    glm::vec3 front;

    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    // angles
    float yaw;
    float pitch;

    // options
    float movementSpeed;
    float mouseSensitivity;
    float fov;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW,
           float pitch = PITCH);

    glm::mat4 getViewMatrix();
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float dx, float dy, bool constrainPitch = true);
    void processMouseScroll(float dy);
};

#endif
