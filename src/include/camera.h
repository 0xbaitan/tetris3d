#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#ifndef CAMERA_IMPLEMENTATION
#define CAMERA_IMPLEMENTATION


class Camera {
public:
    Camera();
    Camera(float starting_pitch, float starting_yaw);
    ~Camera();

    glm::mat4 GetViewMatrix() {
        return view;
    }



    void ProcessInput(bool* keys);
    void ProcessInput(float xoffset, float yoffset);

    glm::mat4 CalculateViewMatrix();

    glm::vec3 GetCameraPosition() const {
        return cameraPos;
    }

    glm::vec3 GetCameraFront() const {
        return cameraFront;
    }

private:
    glm::vec3 worldUp;
    glm::vec3 cameraRight, cameraUp, cameraTarget, cameraPos, cameraFront;
    glm::mat4 view;
    float deltaTime;
    float currentFrame;
    float lastFrame;
    GLfloat cameraSpeed;

    glm::vec3 direction;
   
   
    GLfloat yaw, pitch;

    void UpdateCameraFront();
};

#endif //CAMERA_IMPLEMENTATION