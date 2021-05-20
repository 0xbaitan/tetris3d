#include "block.h"
#include "tetromino.h"
#include <memory>

#ifndef MATRIX_IMPLEMENTATION_H
#define MATRIX_IMPLEMENTATION_H 1

#define MATRIX_ROWS 15
#define MATRIX_COLUMNS 15
#define POS_EMPTY new unsigned int(0)
#define POS_FILLED new unsigned int(1)

class Matrix {

public:
    Matrix();
    ~Matrix();
    void DropIncomingPiece(Movement movement);
    void MoveIncomingPiece(Movement movement);
    bool IsColliding(Movement movement);
    void RotatePiece(Rotation rotation);
    bool CanRotate(Rotation rotation);
    void DeleteLine();
    bool IsGameOver();
    unsigned int GetColorCode(int i, int j) {
        return matrix[i][j];
    }

private:
    Tetromino *current;
    unsigned int matrix[MATRIX_ROWS + 1][MATRIX_COLUMNS + 2];
    int GetInBoundsX(int x);
    int GetInBoundsY(int y);
    void EraseCurrent();
    void KeepCurrent();
    unsigned int GetNewOrientation(Rotation rotation);
};

#endif