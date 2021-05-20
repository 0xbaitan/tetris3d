#include "include/block.h"

Block::Block(unsigned int color, int x, int y) {

    transform = new Transform();
    
    InitColor(color);
    InitMesh(x, y);
}

void Block::InitColor(const int color) {
    float red = ((color >> 16) & 0xFF) / 255.0f;
    float green = ((color >> 8) & 0xFF) / 255.0f;
    float blue = ((color & 0xFF) / 255.0f);
    colorValues[0] = red;
    colorValues[1] = green;
    colorValues[2] = blue;
}

void Block::InitMesh(int x, int y) {

    std::vector<float> vertices;

    vertices.insert(vertices.end(), {    //Face 1
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
        +0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f});

    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < 4 * CUBE_INDICES; i++) {
        indices.push_back(i);
    }

    Material material;
    material.k_ambient = glm::vec3(colorValues[0], colorValues[1], colorValues[2]);
    material.k_diffuse = glm::vec3(colorValues[0], colorValues[1], colorValues[2]);
    material.k_specular = glm::vec3(colorValues[0], colorValues[1], colorValues[2]);
    material.shininess = 20.0f;

    Texture2D *diff_tex = new Texture2D("resources/textures/glass.png", "texture_diffuse");
    Texture2D *spec_tex = new Texture2D("resources/textures/glass.png", "texture_specular");

    diff_tex->LoadTexture();
    spec_tex->LoadTexture();

    textures.push_back(diff_tex);
    textures.push_back(spec_tex);

    mesh = new Mesh(&vertices[0], &indices[0], textures, material, vertices.size(), indices.size());
}

void Block::Move(float x, float y, float z) {
     
   
   
    transform->Translate(x, y, z);
}

void Block::Render(Shader *shader) {
 
    mesh->ApplyTransform(transform);
    shader->SetUniform("model", mesh->GetModelMatrix());
    mesh->RenderMesh(shader);
    transform->Reset();
}
Block::~Block() {
}