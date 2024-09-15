#ifndef CAMERA_H
#define CAMERA_H

#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera {
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    float yaw;
    float pitch;

    float movementSpeed;
    float mouseSensitivity;

    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
    glm::mat4 getViewMatrix();
    void processKeyboard(char direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
private:
    void updateCameraVectors();
};

#endif //CAMERA_H
