#include "include/scene.h"

Scene::Scene(Camera *camera, GWindow *window) {
    this->camera = camera;
    this->window = window;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f,
                                  100.0f);
    //terrain = new Terrain("resources/images/terr.bmp", "resources/textures/brick.jpg");
    Shader* mainShader = new Shader();
    mainShader->CreateFromFiles("resources/shaders/vert.txt", "resources/shaders/frag.txt");
    Shader* stencilShader = new Shader();
    stencilShader->CreateFromFiles("resources/shaders/stencil.vert", "resources/shaders/stencil.frag");
    Shader* shadowShader = new Shader();
    shadowShader->CreateFromFiles("resources/shaders/point_shadow.vert", "resources/shaders/point_shadow.frag", "resources/shaders/point_shadow.geom");

    shaders.insert(shaders.end(), {mainShader, stencilShader, shadowShader});

   
   // shaders[2]
    //meshes.push_back(terrain->GetMesh());
}
void Scene::AddMesh(Mesh *mesh) {
    meshes.push_back(mesh);
}
void Scene::AddModel(Model *model) {
    models.push_back(model);
}
void Scene::AddDirectionalLight(DirectionalLight *light) {
    directionalLights.push_back(light);
}
void Scene::AddPointLight(PointLight *light) {
    pointLights.push_back(light);
}

void Scene::AddPointsLights(PointLight lights[]) {
    pointLights.push_back(&lights[0]);
}

void Scene::RenderScene() {

    glfwPollEvents();

    camera->ProcessInput(window->GetKeys());
    camera->ProcessInput(window->GetChangeX(), window->GetChangeY());

    // InitShadows();

    glViewport(0, 0, window->GetWidth(), window->GetHeight());
    glClearStencil(0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    shaders[0]->UseProgram();

    int count = (int)pointLights.size();

    shaders[0]->SetUniform("pointLightsCount", count);

    shaders[0]->SetUniform("projection", projection);
    shaders[0]->SetUniform("view", camera->CalculateViewMatrix());
    shaders[0]->SetUniform("view_pos", camera->GetCameraPosition());
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0x00);
    ApplyLighting();
    RenderMeshesAndModels(shaders[0]);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    // glDisable(GL_DEPTH);
    shaders[1]->UseProgram();
    shaders[1]->SetUniform("projection", projection);
    shaders[1]->SetUniform("view", camera->CalculateViewMatrix());
    glStencilMask(0x00);
    ResizeMeshesAndModels(shaders[1]);
    glStencilMask(0xFF);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glEnable(GL_DEPTH);
    glDisable(GL_STENCIL_TEST);
    glUseProgram(0);

    window->SwapBuffers();
}

void Scene::ResizeMeshesAndModels(Shader *shader) {
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(1.2f, 1.0f, 2.0f));
    model = glm::scale(model, glm::vec3(1.1f));

    for (size_t index = 0; index < meshes.size(); index++) {
        shader->SetUniform("model", model);
        meshes[index]->RenderMesh(shader);
    }
}

void Scene::RenderMeshesAndModels(Shader *shader) {

    for (size_t index = 0; index < models.size(); index++) {
        shader->SetUniform("model", models[index]->GetModelMatrix());
        models[index]->Render(shader);
    }
    glStencilMask(0xFF);

    for (size_t index = 0; index < meshes.size(); index++) {
        shader->SetUniform("model", meshes[index]->GetModelMatrix());
        meshes[index]->RenderMesh(shader);
    }
}

void Scene::InitShadows() {
    shaders[2]->UseProgram();
    PointShadow *pointShadow;
    for (size_t index = 0; index < pointLights.size(); index++) {
        pointShadow = pointLights[index]->GetShadow();
        glViewport(0, 0, pointShadow->GetShadowWidth(), pointShadow->GetShadowHeight());
        pointShadow->Write();
        glClear(GL_DEPTH_BUFFER_BIT);
        shaders[2]->SetUniform("lightPos", pointLights[index]->pos);
        shaders[2]->SetUniform("far_plane", pointLights[index]->far_plane);
        pointLights[index]->SetLightSpaceMatrix(shaders[2]);
        RenderMeshesAndModels(shaders[2]);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
    glUseProgram(0);
}
void Scene::ApplyLighting() {
    for (size_t index = 0; index < pointLights.size(); index++) {
        pointLights[index]->SetAttributes(shaders[0], index);
        pointLights[index]->SetShadowAttributes(shaders[0], index);
    }
}
Scene::~Scene() {
}