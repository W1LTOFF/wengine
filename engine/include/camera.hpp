#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

const float YAW = -90.f;
const float PITCH = 0.f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float FOV = 45.f;

class Camera {
  private:
    void updateCameraVectors();

  public:
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

    Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f),
           glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), float yaw = YAW,
           float pitch = PITCH);

    glm::mat4 getViewMatrix();
};

#endif
