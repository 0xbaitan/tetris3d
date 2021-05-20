#include <GL/glew.h>
#include <vector>

#include "camera.h"
#include "light.h"
#include "mesh.h"
#include "model.h"
#include "shader.h"
#include "transform.h"
#include "window.h"
#include "terrain.h"

#ifndef SCENE_IMPLEMENTATION_H
#define SCENE_IMPLEMENTATION_H 1

class Scene {
public:
    Scene(Camera *camera, GWindow *window);
    void AddMesh(Mesh *mesh);
    void AddModel(Model *model);
    void AddDirectionalLight(DirectionalLight *light);
    void AddPointLight(PointLight *light);
    void AddPointsLights(PointLight lights[]);
    void RenderScene();
    ~Scene();

private:
    std::vector<Mesh *> meshes;
    std::vector<Model *> models;
    std::vector<DirectionalLight *> directionalLights;
    std::vector<PointLight *> pointLights;
    std::vector<Shader*> shaders;
    Camera *camera;
    GWindow *window;
    Mesh* quad;
    glm::mat4 projection;
    Terrain* terrain;
void ResizeMeshesAndModels(Shader *shader);
    void InitShadows();
    void RenderMeshesAndModels(Shader* shader);
    void ApplyLighting();
};

#endif //SCENE_IMPLEMENTATION_H