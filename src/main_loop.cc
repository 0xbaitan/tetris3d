#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "include/camera.h"
#include "include/light.h"
#include "include/mesh.h"
#include "include/model.h"
#include "include/scene.h"
#include "include/shader.h"
#include "include/shadow.h"
#include "include/texture.h"
#include "include/transform.h"
#include "include/window.h"

#define LEN(a) (sizeof(a) / sizeof(a[0]))

GWindow *window;
Camera *camera;
Scene *scene;

void CreateObjects() {

    unsigned int indices[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

    float vertices[] = {
        //x, y , z, nx, ny, nz, u, v

        //Face 1
        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        //Face 2
        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, +0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        //Face 3
        -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,

        //Face 4
        -0.5f, -0.5f, +0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, +0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        +0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,

        //Face 5
        -0.5f, -0.5f, +0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, +0.5f, +0.5f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f, +0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, +0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f, +0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,

        //Face 6
        +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        +0.5f, +0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        +0.5f, +0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        +0.5f, +0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        +0.5f, -0.5f, +0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f

    };

    Material mat;
    mat.k_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    mat.k_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
    mat.k_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    mat.shininess = 20.0f;
    std::vector<Texture2D *> textures;
    Texture2D *diff_tex = new Texture2D("resources/textures/brick.jpg", "texture_diffuse");
    Texture2D *spec_tex = new Texture2D("resources/textures/brick.jpg", "texture_specular");
    diff_tex->LoadTexture();
    spec_tex->LoadTexture();
    textures.push_back(diff_tex);
    textures.push_back(spec_tex);
    Mesh *mesh = new Mesh(vertices, indices, textures, mat, LEN(vertices), LEN(indices));
    Transform *transform = new Transform();
    transform->Translate(glm::vec3(1.2f, 1.0f, 2.0f));
    mesh->ApplyTransform(transform);
    scene->AddMesh(mesh);
}

int main() {

    window = new GWindow(800, 600, "My Window");
    window->InitialiseWindow();

    camera = new Camera(30.0f, 0.0f);
    scene = new Scene(camera, window);

    CreateObjects();

    window->SetBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
    window->SetDepth();

    Model *floor = new Model("resources/models/floor.obj");
    Transform *floorTransform = new Transform();
    floorTransform->Translate(glm::vec3(1.2f, -1.5f, 2.0f));
    floorTransform->Scale(glm::vec3(0.5f));
    floor->ApplyTransform(floorTransform);
    scene->AddModel(floor);

    PointLight *pointLight = new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(2.0f, 5.0f, 2.0f),
                                            1.0f, 0.09f, 0.032f, 0.1f, 20.0f, 1.0f, 256.0f, 256.0f);

    PointLight *pointLight2 = new PointLight(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(3.0f, 1.0f, 2.0f), 1.0f, 0.09f, 0.032f, 0.1f, 20.f, 1.0f, 256.0f, 256.0f);

    scene->AddPointLight(pointLight);
    scene->AddPointLight(pointLight2);

    while (!window->IsClosing()) {
        scene->RenderScene();
  
    }

    window->DestroyWindow();
    return 0;
}