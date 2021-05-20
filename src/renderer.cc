#include "include/renderer.h"

Renderer::Renderer(Camera *camera, GWindow *window) {
    this->camera = camera;
    this->window = window;
    projection = glm::perspective(glm::radians(60.0f), 800.0f / 600.0f, 0.1f,
                                  100.0f);

    Shader *mainShader = new Shader();
    mainShader->CreateFromFiles("resources/shaders/vert.txt", "resources/shaders/frag.txt");
    Shader *stencilShader = new Shader();
    stencilShader->CreateFromFiles("resources/shaders/stencil.vert", "resources/shaders/stencil.frag");
    Shader *shadowShader = new Shader();
    shadowShader->CreateFromFiles("resources/shaders/point_shadow.vert", "resources/shaders/point_shadow.frag", "resources/shaders/point_shadow.geom");
    transform = new Transform();
    transform->Scale(0.5f, 0.5f, 0.5f);
    shaders.insert(shaders.end(), {mainShader, stencilShader, shadowShader});
    matrix = new Matrix();

    blocks[0] = new Block(RED_COLOR, 1, 1);
    blocks[1] = new Block(LIME_GREEN_COLOR, 1, 1);
    blocks[2] = new Block(CYAN_COLOR, 1, 1);
    blocks[3] = new Block(NAVY_BLUE_COLOR, 1, 1);
    blocks[4] = new Block(ORANGE_COLOR, 1, 1);
    blocks[5] = new Block(YELLOW_COLOR, 1, 1);
    blocks[6] = new Block(PURPLE_COLOR, 1, 1);
    blocks[7] = new Block(CHALK_WHITE_COLOR, 1, 1);

    timer = new Timer(1.00f);
    sidewaysTimer = new Timer(0.25);
}

void Renderer::AddDirectionalLight(DirectionalLight *light) {
    directionalLights.push_back(light);
}
void Renderer::AddPointLight(PointLight *light) {
    pointLights.push_back(light);
}

void Renderer::RenderScene() {

    glfwPollEvents();

    camera->ProcessInput(window->GetKeys());
    camera->ProcessInput(window->GetChangeX(), window->GetChangeY());

    glViewport(0, 0, window->GetWidth(), window->GetHeight());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    shaders[0]->UseProgram();
    glm::mat4 viewMatrix = camera->CalculateViewMatrix();
    
    viewMatrix = Camera::Rotate(viewMatrix, 90.0f, X_AXIS);
    viewMatrix = Camera::Translate(viewMatrix, glm::vec3(0.0f, 6.0f, 0.0f));

    int count = (int)pointLights.size();

    shaders[0]->SetUniform("pointLightsCount", count);

    shaders[0]->SetUniform("projection", projection);
    shaders[0]->SetUniform("view", viewMatrix);
    shaders[0]->SetUniform("view_pos", camera->GetCameraPosition());

    ApplyLighting();

    bool *keys = window->GetKeys();

    if (sidewaysTimer->GetUpdate()) {
        if (keys[GLFW_KEY_UP]) {
            matrix->RotatePiece(CLOCKWISE);
        }
       else if (keys[GLFW_KEY_LEFT]) {
            matrix->DropIncomingPiece(LEFT);
        } else if (keys[GLFW_KEY_RIGHT]) {
            matrix->DropIncomingPiece(RIGHT);
        } else if (keys[GLFW_KEY_DOWN]) {
            matrix->DropIncomingPiece(DOWN);
        }
    
    }
    if (timer->GetUpdate()) {
        matrix->DropIncomingPiece(DOWN);
    }

    RenderMatrix();
    glUseProgram(0);

    window->SwapBuffers();

    // timer->Time(10, SECONDS);
}

void Renderer::ApplyLighting() {
    for (size_t index = 0; index < pointLights.size(); index++) {
        pointLights[index]->SetAttributes(shaders[0], index);
        pointLights[index]->SetShadowAttributes(shaders[0], index);
    }
}

void Renderer::RenderMatrix() {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        for (int j = 0; j < MATRIX_COLUMNS; j++) {
            unsigned int code = matrix->GetColorCode(i, j);
            if (code != 0) {
                RenderBlock(code, i, j, 0);
            }
        }
    }
}

void Renderer::RenderBlock(unsigned int color, int i, int j, int k) {
    switch (color) {
    case PURPLE_COLOR:
        blocks[6]->Move(i, j, k);
        blocks[6]->Render(shaders[0]);
        break;
    case CHALK_WHITE_COLOR:
        blocks[7]->Move(i, j, k);
        blocks[7]->Render(shaders[0]);
        break;
    }
}

Renderer::~Renderer() {
}