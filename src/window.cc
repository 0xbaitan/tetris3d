#include "include/window.h"

GWindow::GWindow() {
    clear_bit = 0;
    width = 800;
    height = 600;
    title = "";
    mouse_first_moved = true;
}

GWindow::GWindow(int width, int height, const char *title) {

    this->width = width;
    this->height = height;
    this->title = title;

    lastx = width / 2.0f;
    lasty = height / 2.0f;
   

    xoffset = 0.0f;
    yoffset = 0.0f;
}

void GWindow::InitialiseWindow() {

    if (!glfwInit()) {
        printf("Error Initializing GLFW.\n");
    }

    //Configuration of Settings
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glewExperimental = GL_TRUE;

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!window) {
        printf("Failed to Create GLFW Window\n");
        glfwTerminate();
        return;
    }
    SetCallbacks();

   // glEnable(GL_DEPTH_TEST);
    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if (error != GLEW_OK) {
        printf("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(window);
        glfwTerminate();
        return;
    }

    glViewport(0, 0, width, height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window, this);
}

void GWindow::DestroyWindow() {
    glfwSetWindowShouldClose(window, GL_TRUE);
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool GWindow::IsClosing() {
    return glfwWindowShouldClose(window) ? true : false;
}

void GWindow::SetCallbacks() {
    glfwSetKeyCallback(window, HandleKeyInput);
    glfwSetCursorPosCallback(window, HandleMouseInput);
}

void GWindow::SetBackgroundColor(float red, float blue, float green, float alpha) {
    glClearColor(red, blue, green, alpha);
    clear_bit |= GL_COLOR_BUFFER_BIT;
}

void GWindow::SetDepth() {
    glEnable(GL_DEPTH_TEST);
    clear_bit |= GL_DEPTH_BUFFER_BIT;
}
void GWindow::Clear() {
    glClear(clear_bit);
}

void GWindow::HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    GWindow *gwindow = static_cast<GWindow *>(glfwGetWindowUserPointer(window));

    if (key >= 0 && key < 1024) {

        if (action == GLFW_PRESS) {
            gwindow->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            gwindow->keys[key] = false;
        }
    }

    if (gwindow->keys[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (gwindow->keys[GLFW_KEY_LEFT_ALT] || gwindow->keys[GLFW_KEY_RIGHT_ALT]) {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    } 

    else if (!gwindow->keys[GLFW_KEY_LEFT_ALT] && !gwindow->keys[GLFW_KEY_RIGHT_ALT]) {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }

}

void GWindow::HandleMouseInput(GLFWwindow *window, double xpos, double ypos) {
    GWindow *gwindow = static_cast<GWindow *>(glfwGetWindowUserPointer(window));
    if (gwindow->mouse_first_moved) {
        gwindow->lastx = xpos;
        gwindow->lasty = ypos;
        gwindow->mouse_first_moved = false;
    }
   
    gwindow->xoffset = xpos - gwindow->lastx;
    gwindow->yoffset = ypos - gwindow->lasty;

    gwindow->lastx = xpos;
    gwindow->lasty = ypos;
   
   float sensitivity = 0.1f;
    gwindow->xoffset *= sensitivity;
    gwindow->yoffset *= sensitivity;

   // printf("xoffset: %f, yoffset: %f\n", gwindow->xoffset, gwindow->yoffset);
}

float GWindow::GetChangeX() {
    float current_xoffset = xoffset;
    xoffset = 0;
    return current_xoffset;
}

float GWindow::GetChangeY() {
    float current_yoffset = yoffset;
    yoffset = 0;
    return current_yoffset;
}

GWindow::~GWindow() {
    DestroyWindow();
}