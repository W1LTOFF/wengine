#include "camera.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_geometric.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : front(glm::vec3(0.0f, 0.0f, -1.0f)), movementSpeed(SPEED),
      mouseSensitivity(SENSITIVITY), fov(FOV) {
    this->position = position;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;
    updateCameraVectors();
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this->position, this->position + this->front, this->up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
    float velocity = this->movementSpeed * deltaTime;
    if (direction == FORWARD) {
        this->position += this->front * velocity;
    }
    if (direction == BACKWARD) {
        this->position -= this->front * velocity;
    }
    if (direction == RIGHT) {
        this->position += this->right * velocity;
    }
    if (direction == LEFT) {
        this->position -= this->right * velocity;
    }
    if (direction == UP) {
        this->position += this->worldUp * velocity;
    }
    if (direction == DOWN) {
        this->position -= this->worldUp * velocity;
    }
}

void Camera::processMouseMovement(float dx, float dy, bool constrainPitch) {
    dx *= this->mouseSensitivity;
    dy *= this->mouseSensitivity;

    this->yaw += dx;
    this->pitch += dy;

    if (constrainPitch) {
        if (pitch > 89.0f) {
            pitch = 89.0f;
        }
        if (pitch < -89.0f) {
            pitch = -89.0f;
        }
    }
    updateCameraVectors();
}

void Camera::processMouseScroll(float dy) {
    this->fov -= dy;
    if (this->fov < 1.f) {
        this->fov = 1.f;
    }
    if (this->fov > 90.f) {
        this->fov = 90.f;
    }
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(front);

    this->right = glm::normalize(glm::cross(this->front, this->worldUp));
    this->up = glm::normalize(glm::cross(this->right, this->front));
}
