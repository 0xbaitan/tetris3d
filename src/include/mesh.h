
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>

#include "shader.h"
#include "texture.h"
#include "transform.h"

#ifndef MESH_IMPLEMENTATION
#define MESH_IMPLEMENTATION

struct Vertex {
    glm::vec3 position;
    glm::vec3 normals;
    glm::vec2 texture_coordinates;
};

struct Material {
    glm::vec3 k_ambient;
    glm::vec3 k_diffuse;
    glm::vec3 k_specular;
    float shininess;
};

class Mesh {
public:
    Mesh();
    Mesh(GLfloat *vertices, GLuint *indices, std::vector<Texture2D *> textures, Material material, size_t num_vertices, size_t num_indices);

    void ConstructMesh();
    void RenderMesh(Shader *shader);
    void ClearMesh();
    void ApplyTransform(Transform *transform);
    glm::mat4 GetModelMatrix();

    ~Mesh();

private:
    GLuint VAO, VBO, EBO;
    size_t num_vertices, num_indices;

    GLfloat *vertices;
    GLuint *indices;
    std::vector<Texture2D *> textures;
    Material material;
    Transform *transform;

    unsigned int indexCount;
};

#endif //MESH_IMPLEMENTATION