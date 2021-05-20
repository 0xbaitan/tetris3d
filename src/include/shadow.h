#include <GL/glew.h>

#ifndef SHADOW_IMPLEMENTATION
#define SHADOW_IMPLEMENTATION 1

class Shadow {

public:
    Shadow(unsigned int shadow_height, unsigned int shadow_width);
    void CreateDepthMap();
    unsigned int GetShadowHeight() const { return height; }
    unsigned int GetShadowWidth() const { return width; }
    unsigned int GetID() const { return FBO; }
    unsigned int GetDepthMapID() const { return depthMap; }
    void Write();
    void Read(GLenum tex_unit);

private:
    unsigned int height, width;
    unsigned int FBO;
    unsigned int depthMap;
};

class PointShadow {
public:
    PointShadow(unsigned int shadow_height, unsigned int shadow_width);
    void CreateShadowMap();
    void Write();
    unsigned int GetShadowHeight() const { return height; }
    unsigned int GetShadowWidth() const { return width; }
    unsigned int GetDepthMapID() const { return depth_cube_map; }
    void Read(GLenum texUnit);

private:
    unsigned int height, width;
    unsigned int depth_cube_map;
    unsigned int FBO;
};

#endif