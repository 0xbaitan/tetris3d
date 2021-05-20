#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

#ifndef CAMERA_IMPLEMENTATION
#define CAMERA_IMPLEMENTATION

#define TOP_VIEW_POS glm::vec3(-22.704155, 6.872361, -0.159438);
#define FRONT_VIEW_POS glm::vec3(6.819733f, 5.148967, 26.881672);
#define DEFAULT_POS glm::vec3(-4.712718f, -8.316400f, 3.0f);

#define X_AXIS glm::vec3(1.0f, 0.0f, 0.0f)
#define Y_AXIS glm::vec3(0.0f, 1.0f, 0.0f)
#define Z_AXIS glm::vec3(0.0f, 0.0f, 1.0f)

class Camera {
public:
    Camera();
    Camera(float starting_pitch, float starting_yaw);
    ~Camera();

    glm::mat4 GetViewMatrix() {
        return view;
    }

    void ProcessInput(bool *keys);
    void ProcessInput(float xoffset, float yoffset);

    glm::mat4 CalculateViewMatrix();

    glm::vec3 GetCameraPosition() const {
        return cameraPos;
    }

    glm::vec3 GetCameraFront() const {
        return cameraFront;
    }

    static glm::mat4 Rotate(glm::mat4 matrix, float degree, glm::vec3 axis);
    static glm::mat4 Translate(glm::mat4 matrix, glm::vec3 vector);

    

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