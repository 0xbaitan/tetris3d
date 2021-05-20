#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#include "include/texture.h"

Texture2D::Texture2D(std::string path, std::string type) {
    textureID = 0;
    this->path = path;
    this->type = type;
}

void Texture2D::SetBorderColor(float *color) {
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
}

unsigned int Texture2D::LoadTexture() {

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    WrapTexture(GL_REPEAT, GL_REPEAT);
    FilterTexture(GL_NEAREST, GL_NEAREST);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(path.data(), &width, &height, &nrChannels, 0);

    if (!data) {
        printf("Failed to load texture From Path: %s\n", path.c_str());
        return 0;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, data);

    stbi_image_free(data);
    return textureID;
}

void Texture2D::WrapTexture(GLint wrap_s, GLint wrap_t) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t);
}

void Texture2D::FilterTexture(GLint min_filter, GLint mag_filter) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

void Texture2D::FilterMipMapLevels(GLint min_filter, GLint mag_filter) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}

void Texture2D::UseTexture(GLuint texture_unit) {
    if (!(texture_unit >= 0 && texture_unit <= 15)) {
        printf("Texture Unit Out Of Bounds\n");
        return;
    }
    glActiveTexture(GL_TEXTURE0 + texture_unit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture2D::UnuseTexture() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture2D::~Texture2D() {
}
