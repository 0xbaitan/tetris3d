#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "include/camera.h"
#include "include/light.h"
#include "include/matrix.h"
#include "include/mesh.h"
#include "include/model.h"
#include "include/renderer.h"
#include "include/shader.h"
#include "include/shadow.h"
#include "include/tetromino.h"
#include "include/texture.h"
#include "include/transform.h"
#include "include/window.h"

#define LEN(a) (sizeof(a) / sizeof(a[0]))

GWindow *window;
Camera *camera;
Renderer *renderer;

int main() {

    window = new GWindow(800, 600, "My Window");
    window->InitialiseWindow();

    camera = new Camera(70.0f, -30.0f);


    window->SetBackgroundColor(0.0f, 0.0f, 0.0f, 1.0f);
    window->SetDepth();

    

    PointLight *pointLight = new PointLight(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f),
                                            glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(2.0f, 5.0f, 2.0f),
                                            1.0f, 0.09f, 0.032f, 0.1f, 20.0f, 1.0f, 256.0f, 256.0f);

    PointLight *pointLight2 = new PointLight(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), glm::vec3(3.0f, 1.0f, 2.0f), 1.0f, 0.09f, 0.032f, 0.1f, 20.f, 1.0f, 256.0f, 256.0f);
   
    renderer = new Renderer(camera, window);
    renderer->AddPointLight(pointLight);
    renderer->AddPointLight(pointLight2);

    while (!window->IsClosing()) {
        renderer->RenderScene();
    }

    window->DestroyWindow();
    return 0;
}