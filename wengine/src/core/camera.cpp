#include "wengine/camera.hpp"

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
    if (mouseActive) {
        float velocity = this->movementSpeed * deltaTime;
        glm::vec3 velocityVec = {0.f, 0.f, 0.f};
        if (direction == FORWARD) {
            velocityVec += this->front * velocity;
        }
        if (direction == BACKWARD) {
            velocityVec -= this->front * velocity;
        }
        if (direction == RIGHT) {
            velocityVec += this->right * velocity;
        }
        if (direction == LEFT) {
            velocityVec -= this->right * velocity;
        }
        if (direction == UP) {
            velocityVec += this->worldUp * velocity;
        }
        if (direction == DOWN) {
            velocityVec -= this->worldUp * velocity;
        }

        this->position += velocityVec;
    }
}

void Camera::processMouseMovement(float dx, float dy, bool constrainPitch) {
    if (mouseActive) {
        dx *= this->mouseSensitivity;
        dy *= this->mouseSensitivity;

        this->yaw += dx;
        this->pitch += dy;
        if (constrainPitch) {
            if (pitch > 89.f) {
                pitch = 89.f;
            }
            if (pitch < -89.f) {
                pitch = -89.f;
            }
        }
        if (yaw > 360.f) {
            yaw = 0.f;
        }
        if (yaw < -360.f) {
            yaw = 0.f;
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
