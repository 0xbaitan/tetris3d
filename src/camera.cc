#include "include/camera.h"
#include <stdio.h>
Camera::Camera(float starting_pitch, float starting_yaw) {

    view = glm::mat4(1.0f);
    cameraPos = glm::vec3(0.0f, 0.0f, 1.0f);
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
    //  printf("Delta Time: %f\n", deltaTime);
    float velocity = cameraSpeed * deltaTime;

    if (keys[GLFW_KEY_UP]) {
        cameraPos += velocity * cameraFront;
       // printf("forward!\n");
    } else if (keys[GLFW_KEY_DOWN]) {
        cameraPos -= velocity * cameraFront;
       // printf("backward!\n");
    } else if (keys[GLFW_KEY_RIGHT]) {
        cameraPos += velocity * cameraRight;
      //  printf("right!\n");
    } else if (keys[GLFW_KEY_LEFT]) {
        cameraPos -= velocity * cameraRight;
        //printf("left!\n");
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
