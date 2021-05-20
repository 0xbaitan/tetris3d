#include "include/tetromino.h"

Tetromino::Tetromino(unsigned int color, Flag flag) {

    x = 0;
    y = 6;
    orientation = 0;

    switch (flag) {
    case I_FLAG:
        Init(color, I_BASE);
        break;
    case O_FLAG:
        Init(color, O_BASE);
        break;
    case T_FLAG:
        Init(color, T_BASE);
        break;
    case S_FLAG:
        Init(color, S_BASE);
        break;
    case Z_FLAG:
        Init(color, Z_BASE);
        break;
    case J_FLAG:
        Init(color, J_BASE);
        break;
    case L_FLAG:
        Init(color, L_BASE);
        break;
    default:
        break;
    }
}

void Tetromino::Init(unsigned int color, const bool base[ORIENTATIONS][NUM_BLOCKS][NUM_BLOCKS]) {
    for (int o = 0; o < ORIENTATIONS; o++) {
        for (int y = 0; y < NUM_BLOCKS; y++) {
            for (int x = 0; x < NUM_BLOCKS; x++) {
                if (base[o][x][y]) {
                    tetromino[o][x][y] = color;
                } else {
                    tetromino[o][x][y] = 0;
                }
            }
        }
    }
}

unsigned int Tetromino::GetOrientation() {
    return orientation;
}

void Tetromino::SetOrientation(unsigned int orientation) {
    this->orientation = orientation;
}
Tetromino::~Tetromino() {
}