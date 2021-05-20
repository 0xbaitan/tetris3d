#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <GL/glew.h>
#include <vector>

#include "camera.h"
#include "light.h"
#include "mesh.h"

#include "shader.h"
#include "transform.h"
#include "window.h"

#include "block.h"
#include "matrix.h"
#include "timer.h"

class Renderer {
public:
    Renderer(Camera *camera, GWindow *window);
    void AddMesh(Mesh *mesh);

    void AddDirectionalLight(DirectionalLight *light);
    void AddPointLight(PointLight *light);
    void RenderScene();
    void RenderMatrix();
    ~Renderer();

private:
    Matrix *matrix;

    std::vector<DirectionalLight *> directionalLights;
    std::vector<PointLight *> pointLights;
    std::vector<Shader *> shaders;
    Camera *camera;
    GWindow *window;
    Timer* timer;
    Timer* sidewaysTimer;
    Block *blocks[8];

    Transform *transform;
    glm::mat4 projection;
    void ApplyLighting();
    void RenderBlock(unsigned int color, int i, int j, int k);
};

#endif