#include "include/model.h"

void Model::Render(Shader* shader) {
    for (size_t i = 0; i < meshes.size(); i++) {
        meshes[i]->RenderMesh(shader);
    }
}

void Model::LoadModel(std::string path) {
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate |
                                                     aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_JoinIdenticalVertices);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of("/"));
    //   printf("directory: %s\n", directory.data());
    ProcessNode(scene->mRootNode, scene);
    printf("Model Loading Done\n");
}

void Model::ProcessNode(aiNode *node, const aiScene *scene) {
    // process all the node’s meshes (if any)
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }
    // then do the same for each of its children
    for (size_t i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
        // printf("Done: %ld\n", i);
    }
}

void Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {

    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D *> textures;

    for (size_t i = 0; i < mesh->mNumVertices; i++) {

        //Process vertex positions, normals and texture coordinates
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        vertices.insert(vertices.end(), {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});

        if (mesh->mTextureCoords[0]) {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        } else {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }

        // printf("X: %lf, Y: %lf, Z: %lf, NX: %lf, NY: %lf, NZ: %lf, U: %lf, V: %lf\n", vertex.position.x, vertex.position.y, vertex.position.z, vertex.normals.x, vertex.normals.y, vertex.normals.z, vertex.texture_coordinates.x, vertex.texture_coordinates.y);
    }
    // Process indices
    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            //     printf("%d ", face.mIndices[j]);
            indices.push_back(face.mIndices[j]);
        }
        //  printf("\n");
    }

    Material m_material;

    // Process material
    if (mesh->mMaterialIndex >= 0) {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        aiColor3D color;

        material->Get(AI_MATKEY_COLOR_AMBIENT, color);
        m_material.k_ambient = glm::vec3(color.r, color.g, color.b);

        material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
        m_material.k_diffuse = glm::vec3(color.r, color.g, color.b);

        material->Get(AI_MATKEY_COLOR_SPECULAR, color);
        m_material.k_specular = glm::vec3(color.r, color.g, color.b);

        GLfloat shininess;

        material->Get(AI_MATKEY_SHININESS, shininess);
        m_material.shininess = shininess;

        std::vector<Texture2D *> diffuseMaps = LoadMaterialTextures(material,
                                                                    aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture2D *> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(),
                        specularMaps.end());
    } else {
        m_material.k_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
        m_material.k_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
        m_material.k_specular = glm::vec3(1.0f, 1.0f, 1.0f);
    }
    //printf("Is textures empty: %d\n", textures.empty());
    if (textures.empty()) {
        Texture2D *blank_diffuse_texture = new Texture2D("resources/textures/blank.jpg", "texture_diffuse");
        Texture2D *blank_specular_texture = new Texture2D("resources/textures/blank.jpg", "texture_specular");

        blank_diffuse_texture->LoadTexture();
        blank_specular_texture->LoadTexture();

        textures.insert(textures.end(), blank_diffuse_texture);
        textures.insert(textures.end(), blank_specular_texture);
    }

    //   printf("(Model) vertices: %ld, indices: %ld\n", vertices.size(), indices.size());
    Mesh *nmesh;

    nmesh = new Mesh(&vertices[0], &indices[0], textures, m_material, vertices.size(), indices.size());

    meshes.push_back(nmesh);
}

std::vector<Texture2D *> Model::LoadMaterialTextures(aiMaterial *material,
                                                     aiTextureType type, std::string typeName) {
    std::vector<Texture2D *> textures;
    aiString path;
    
    for (size_t i = 0; i < material->GetTextureCount(type); i++) {

        if (!material->GetTexture(type, i, &path) == AI_SUCCESS) {
            return textures;
        }
        bool skip = false;
        for (size_t j = 0; j < textures_loaded.size(); j++) {

            if (std::strcmp(textures_loaded[j]->GetPath().data(), path.C_Str()) == 0) {
                textures.push_back(textures_loaded[j]);
                skip = true;
            }
        }

        if (!skip) {
            Texture2D *texture = new Texture2D(path.C_Str(), typeName.data());
            texture->LoadTexture();
            textures_loaded.push_back(texture);
            textures.push_back(texture);
        }
    }
    //printf("%s\n", path.C_Str());
    return textures;
}

void Model::ApplyTransform(Transform *transform) {
    this->transform = transform;
}
glm::mat4 Model::GetModelMatrix() {
    return transform->GetModel();
}