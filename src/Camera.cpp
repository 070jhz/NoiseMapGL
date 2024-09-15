#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"

#include <glm/gtc/quaternion.hpp>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : position(position), worldUp(up), yaw(yaw), pitch(pitch),
      movementSpeed(2.5f), mouseSensitivity(0.1f) {
    front = glm::vec3(0.0f, 0.0f, -1.0f); // initialize front direction
    updateCameraVectors(); // calculate up, right, and front
}

glm::mat4 Camera::getViewMatrix() {
    return lookAt(position, position+front, up);
}

void Camera::processKeyboard(char direction, float deltaTime) {
    float velocity = movementSpeed*deltaTime;
    switch (direction) {
    case 'W':
        position += front * velocity * 100.0f;
        break;
    case 'S':
        position -= front * velocity * 100.0f;
        break;
    case 'A':
        position -= right * velocity * 100.0f;
        break;
    case 'D':
        position += right * velocity * 100.0f;
        break;
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch) {
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw += xOffset;
    pitch -= yOffset;

    if (constrainPitch) {
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->front = glm::normalize(newFront);

    this->right = glm::normalize(glm::cross(front, worldUp));
    this->up = glm::normalize(glm::cross(right, front));
}

