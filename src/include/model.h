#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "mesh.h"
#include "transform.h"
// #include "shader.h"
// #include "texture.h"

#ifndef MODEL_IMPLEMENTATION
#define MODEL_IMPLEMENTATION

class Model {
public:
    Model(std::string path) {
        transform = new Transform();
        LoadModel(path);
    }

    void Render(Shader *shader);

    void ApplyTransform(Transform *transform);
    glm::mat4 GetModelMatrix();

private:
    // model data
    std::vector<Mesh *> meshes;

    std::vector<Texture2D *> textures_loaded;

    std::string directory;

    Transform *transform;

    void LoadModel(std::string path);

    void ProcessNode(aiNode *node, const aiScene *scene);

    void ProcessMesh(aiMesh *mesh, const aiScene *scene);

    std::vector<Texture2D *> LoadMaterialTextures(aiMaterial *material,
                                                  aiTextureType type, std::string typeName);
};

#endif //MODEL_IMPLEMENTATION