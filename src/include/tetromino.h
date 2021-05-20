#include "block.h"
#include "mesh.h"
#include "shader.h"
#include "tetris_attrib.h"
#include <vector>
#ifndef Tetromino_IMPLEMENTATION_H
#define Tetromino_IMPLEMENTATION_H 1

#define NUM_BLOCKS 5
#define ORIENTATIONS 4

const bool I_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {1, 1, 1, 1, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 1, 0}}};

const bool O_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}};

const bool T_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 1, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}}};

const bool S_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}}};

const bool Z_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}}};

const bool J_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 1, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 1, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 0, 0, 0}}};

const bool L_BASE[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS] =
    {{{0, 0, 0, 0, 0},
      {0, 0, 0, 1, 0},
      {0, 1, 1, 1, 0},
      {0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 1, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 0, 0, 0, 0},
      {0, 1, 1, 1, 0},
      {0, 1, 0, 0, 0},
      {0, 0, 0, 0, 0}},

     {{0, 0, 0, 0, 0},
      {0, 1, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 1, 0, 0},
      {0, 0, 0, 0, 0}}};

enum Flag {
    //Shapes
    I_FLAG,
    O_FLAG,
    T_FLAG,
    S_FLAG,
    Z_FLAG,
    J_FLAG,
    L_FLAG,

};

enum Movement {
    LEFT,
    RIGHT,
    DOWN
};

enum Rotation {
    CLOCKWISE,
    ANTI_CLOCKWISE
};

class Tetromino {
public:
    Tetromino(unsigned int color, Flag flag);

    unsigned int GetCodeAt(int orientation, int i, int j) {
        return tetromino[orientation][i][j];
    }
    unsigned int GetX() const { return x; }
    unsigned int GetY() const { return y; }
    void SetX(unsigned int x) { this->x = x; }
    void SetY(unsigned int y) { this->y = y; }
     unsigned int GetOrientation();
    void SetOrientation(unsigned int orientation);
    ~Tetromino();

private:
    unsigned int x;
    unsigned int y;
    unsigned int color;
    unsigned int tetromino[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS];
    unsigned int orientation;

    void Init(unsigned int color, const bool base[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS]);
};

#endif