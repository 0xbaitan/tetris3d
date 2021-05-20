#include "include/camera.h"
#include <stdio.h>
Camera::Camera(float starting_pitch, float starting_yaw) {

    view = glm::mat4(1.0f);
    cameraPos = DEFAULT_POS;

    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraFront = glm::normalize(cameraPos - cameraTarget);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));

    cameraSpeed = 2.5f;

    currentFrame = 0.0f;
    lastFrame = 0.0f;
    deltaTime = 0.0f;

    pitch = starting_pitch;
    yaw = starting_yaw;
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::ProcessInput(bool *keys) {

    currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    float velocity = cameraSpeed * deltaTime;

    if (keys[GLFW_KEY_W]) {
        cameraPos += velocity * cameraFront;
        // printf("forward!\n");
    } else if (keys[GLFW_KEY_S]) {
        cameraPos -= velocity * cameraFront;
        // printf("backward!\n");
    } else if (keys[GLFW_KEY_D]) {
        cameraPos += velocity * cameraRight;
        //  printf("right!\n");
    } else if (keys[GLFW_KEY_A]) {
        cameraPos -= velocity * cameraRight;
        //printf("left!\n");
    } else if (keys[GLFW_KEY_M]) {
        printf("%ff, %ff, %ff\n", cameraPos.x, cameraPos.y, cameraPos.z);
    } else if (keys[GLFW_KEY_0]) {
        cameraPos = TOP_VIEW_POS;
    } else if (keys[GLFW_KEY_1]) {
        cameraPos = FRONT_VIEW_POS;
    }
}

void Camera::ProcessInput(float xoffset, float yoffset) {
    pitch -= yoffset;
    yaw += xoffset;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    UpdateCameraFront();
}

void Camera::UpdateCameraFront() {
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    cameraFront = glm::normalize(direction);

    cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
    cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
 glm::mat4 Camera::Rotate(glm::mat4 matrix, float degree, glm::vec3 axis) {
    return glm::rotate(matrix, glm::radians(degree), axis);
}
 glm::mat4 Camera::Translate(glm::mat4 matrix, glm::vec3 vector) {
    return glm::translate(matrix, vector);
}