#ifndef _BLOCK_H_
#define _BLOCK_H_ 1

#include "mesh.h"
#include "tetris_attrib.h"

#include <vector>



#define VERTEX_POS 0.5f
#define CUBE_VERTEX_ATTRIB (6 * 6 * 8)
#define CUBE_INDICES (6 * 6)



class Block {
public:
    Block(unsigned int color, int x, int y);

    void Render(Shader* shader);
    void Move(float x, float y, float z);

    ~Block();

private:
    float colorValues[3];
    Mesh *mesh;
    Transform *transform;
    std::vector<Texture2D *> textures;
    void InitColor(const int color);
    void InitMesh(int x, int y);
    
   
};

#endif