#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdio.h>

#ifndef WINDOW_IMPLEMENTATION
#define WINDOW_IMPLEMENTATION


class GWindow {

public:
    GWindow();
    GWindow(int height, int width, const char *title);

    void InitialiseWindow();
    void DestroyWindow();
    bool IsClosing();

    int GetWidth() const {
        return width;
    }

    int GetHeight() const {
        return height;
    }

    bool *GetKeys() {
        return keys;
    }

    float GetChangeX();
      
    float GetChangeY();
  
    void SetBackgroundColor(float red, float blue, float green, float alpha);
    void SetDepth();
    void Clear();
    void SwapBuffers() { return glfwSwapBuffers(window); }

    ~GWindow();

private:
    GLbitfield clear_bit;
    int width, height;
    const char *title;
    GLFWwindow *window;
    bool keys[1024];

    GLfloat lastx, lasty;
    GLfloat xoffset, yoffset;
    
    bool mouse_first_moved;

    void SetCallbacks();
    static void HandleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void HandleMouseInput(GLFWwindow *window, double xpos, double ypos);
};

#endif //WINDOW_IMPLEMENTATION