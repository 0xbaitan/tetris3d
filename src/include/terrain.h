#include "mesh.h"
#include "texture.h"
#include <fstream>
#include <vector>
#ifndef TERRAIN_IMPEMENTATION_H
#define TERRAIN_IMPLEMENTATION_H 1

class Terrain {
public:
    Terrain(const char *heightMapPath, const char *texturePath);
    ~Terrain();
    Mesh *GetMesh() {
        return terrain;
    }

private:
    const unsigned int TERRAIN_LENGTH = 2;
    const unsigned int TERRAIN_BREADTH = 2;
    const unsigned int TERRAIN_HEIGHT = 720;
    std::vector<float> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture2D *> textures;
    Mesh *terrain;
    Material material;
    bool LoadHeightMap(const char *heightMapPath, unsigned char bitsPerPixel, unsigned int width, unsigned int height);
    void AssignIndices(unsigned int width, unsigned int height);
    inline int GetFileLength(std::istream &file);
    inline float GetHeightValue(const unsigned char *data, unsigned char numBytes);
};

#endif