
#include "include/mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    EBO = 0;
    indexCount = 0;
}

Mesh::Mesh(GLfloat *vertices, GLuint *indices, std::vector<Texture2D *> textures, Material material, size_t num_vertices, size_t num_indices) {
    //printf("Vertices: %ld Indices: %ld Textures: %ld\n", vertices.size(), indices.size(), textures.size());
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;
    this->material = material;

    this->num_vertices = num_vertices;
    this->num_indices = num_indices;

    transform = new Transform();

    VAO = 0;
    VBO = 0;
    EBO = 0;
    indexCount = 0;

    ConstructMesh();
}

void Mesh::ConstructMesh() {

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, num_indices * sizeof(GLuint), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, num_vertices * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

    //Vertex Information To Shader: Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
    glEnableVertexAttribArray(0);

    //Vertex Information To Shader: Normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    //Vertex Information To Shader: Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh(Shader* shader) {

    // printf("Diffuse: %f %f %f\n", material.k_diffuse.x, material.k_diffuse.y, material.k_diffuse.z);
    /* Apply all non-texture related attributes to the mesh */
    shader->SetUniform("material.ambient", material.k_ambient);
    shader->SetUniform("material.diffuse", material.k_diffuse);
    shader->SetUniform("material.specular", material.k_specular);
    shader->SetUniform("material.shininess", material.shininess);

    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;

    // textures[0]->UseTexture(0);
    // shader->SetUniform("texture_diffuse0", 0);
    // textures[1]->UseTexture(1);
    // shader->SetUniform("texture_specular0", 1);

    for (unsigned int i = 0; i < textures.size(); i++) {

        textures[i]->UseTexture(i);
        // activate texture unit first
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = textures[i]->GetType();
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);
        shader->SetUniform(name + number, i);
      //  printf("material.%s%s\n", name.c_str(), number.c_str());
        // textures[i]->UnuseTexture();
    }

    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, num_indices, GL_UNSIGNED_INT, 0);
    // printf("Drawn\n");
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (EBO != 0) {
        glDeleteBuffers(1, &EBO);
    }
}

void Mesh::ApplyTransform(Transform *transform) {
    this->transform = transform;
}

glm::mat4 Mesh::GetModelMatrix() {
    return transform->GetModel();
}

Mesh::~Mesh() {
    ClearMesh();
}