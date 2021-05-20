
#include <GL/glew.h>
#include <string>

#ifndef TEXTURE_IMPLEMENTATION
#define TEXTURE_IMPLEMENTATION

class Texture2D {
public:
    Texture2D(std::string path, std::string type);
    ~Texture2D();

    void SetBorderColor(float *color);
    unsigned int LoadTexture();
    void WrapTexture(GLint wrap_s, GLint wrap_t);
    void FilterTexture(GLint min_filter, GLint mag_filter);
    void FilterMipMapLevels(GLint min_filter, GLint mag_filter);
    void UseTexture(GLuint texture_unit);
    void UnuseTexture();

    std::string GetType() const {
        return type;
    }

    unsigned int GetID() const {
        return textureID;
    }

    std::string GetPath() const {
        return path;
    }

private:
    GLuint textureID;
    std::string type;
    std::string path;
};

#endif //TEXTURE_IMPLEMENTATION
