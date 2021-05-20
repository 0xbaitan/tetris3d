#include "include/matrix.h"

Matrix::Matrix() {

    current = nullptr;

    for (unsigned int i = 0; i < MATRIX_ROWS; i++) {
        for (unsigned int j = 0; j < MATRIX_COLUMNS; j++) {
            if (j == 0 || j == MATRIX_COLUMNS - 1)
                matrix[i][j] = CHALK_WHITE_COLOR;
            else if (i == MATRIX_ROWS - 1)
                matrix[i][j] = CHALK_WHITE_COLOR;
            else
                matrix[i][j] = 0;
        }
    }
}

void Matrix::DropIncomingPiece(Movement movement) {
    if (!current) {
        current = new Tetromino(PURPLE_COLOR, Flag::S_FLAG);
    }
    if (!IsColliding(movement))
        MoveIncomingPiece(movement);
}

void Matrix::MoveIncomingPiece(Movement movement) {
    unsigned int x = current->GetX();
    unsigned int y = current->GetY();

    EraseCurrent();

    switch (movement) {
    case LEFT:
        y = (y - 1 < 0) ? 0 : y - 1;
        current->SetY(y);
        break;
    case DOWN:
        x = (x + 1 >= MATRIX_ROWS) ? MATRIX_ROWS - 1 : x + 1;
        current->SetX(x);
        break;
    case RIGHT:
        y = (y + 1 >= MATRIX_COLUMNS) ? MATRIX_COLUMNS - 1 : y + 1;
        current->SetY(y);
        break;
    default:
        break;
    }
    KeepCurrent();
}

void Matrix::EraseCurrent() {
    unsigned int x = current->GetX();
    unsigned int y = current->GetY();
    unsigned int orientation = current->GetOrientation();
    for (int i = 0; i < NUM_BLOCKS; i++) {
        for (int j = 0; j < NUM_BLOCKS; j++) {
            if (current->GetCodeAt(orientation, i, j) != 0)
                matrix[GetInBoundsX(x + i)][GetInBoundsY(y + j)] = 0;
        }
    }
}

void Matrix::KeepCurrent() {
    unsigned int x = current->GetX();
    unsigned int y = current->GetY();
    unsigned int orientation = current->GetOrientation();
    unsigned int code;
    for (unsigned int i1 = x, i2 = 0; i1 < x + NUM_BLOCKS && i2 < NUM_BLOCKS; i1++, i2++) {
        for (unsigned int j1 = y, j2 = 0; j1 < y + NUM_BLOCKS && i2 < NUM_BLOCKS; j1++, j2++) {
            code = current->GetCodeAt(orientation, i2, j2);
            if (code != 0)
                matrix[i1][j1] = code;
        }
    }
}

bool Matrix::IsColliding(Movement movement) {
    unsigned int x = current->GetX();
    unsigned int y = current->GetY();
    unsigned int orientation = current->GetOrientation();
    EraseCurrent();

    switch (movement) {
    case LEFT:
        y--;
        for (unsigned int i1 = x + NUM_BLOCKS - 1, i2 = NUM_BLOCKS - 1; i1 >= x && i2 >= 0; i1--, i2--) {
            for (unsigned int j1 = y + NUM_BLOCKS - 1, j2 = NUM_BLOCKS - 1; j1 >= y && j2 >= 0; j1--, j2--) {
                if (matrix[GetInBoundsX(i1)][GetInBoundsY(j1)] != 0 && current->GetCodeAt(orientation, i2, j2) != 0) {
                    printf("matrix[%d][%d]=%d && tetromino[%d][%d]=%d\n", GetInBoundsX(i1), GetInBoundsY(j1), matrix[GetInBoundsX(i1)][GetInBoundsY(j1)], i2, j2, current->GetCodeAt(orientation, i2, j2));
                    KeepCurrent();
                    return true;
                }
            }
        }
        break;
    case DOWN:
        x++;
        for (unsigned int i1 = x, i2 = 0; i1 < x + NUM_BLOCKS && i2 < NUM_BLOCKS; i1++, i2++) {
            for (unsigned int j1 = y, j2 = 0; j1 < y + NUM_BLOCKS && j2 < NUM_BLOCKS; j1++, j2++) {
                if (matrix[GetInBoundsX(i1)][GetInBoundsY(j1)] != 0 && current->GetCodeAt(orientation, i2, j2) != 0) {
                    printf("matrix[%d][%d]=%d && tetromino[%d][%d]=%d\n", GetInBoundsX(i1), GetInBoundsY(j1), matrix[GetInBoundsX(i1)][GetInBoundsY(j1)], i2, j2, current->GetCodeAt(orientation, i2, j2));
                    KeepCurrent();
                    return true;
                }
            }
        }
        break;
    case RIGHT:
        y++;
        for (unsigned int i1 = x, i2 = 0; i1 < x + NUM_BLOCKS && i2 < NUM_BLOCKS; i1++, i2++) {
            for (unsigned int j1 = y, j2 = 0; j1 < y + NUM_BLOCKS && j2 < NUM_BLOCKS; j1++, j2++) {
                if (matrix[GetInBoundsX(i1)][GetInBoundsY(j1)] != 0 && current->GetCodeAt(orientation, i2, j2) != 0) {
                    printf("matrix[%d][%d]=%d && tetromino[%d][%d]=%d\n", GetInBoundsX(i1), GetInBoundsY(j1), matrix[GetInBoundsX(i1)][GetInBoundsY(j1)], i2, j2, current->GetCodeAt(orientation, i2, j2));
                    KeepCurrent();
                    return true;
                }
            }
        }
        break;
    default:
        break;
    }

    KeepCurrent();
    return false;
}

int Matrix::GetInBoundsX(int x) {
    if (x < 0)
        return 0;
    if (x >= MATRIX_ROWS)
        return MATRIX_ROWS - 1;
    return x;
}
int Matrix::GetInBoundsY(int y) {
    if (y < 0)
        return 0;
    if (y >= MATRIX_COLUMNS)
        return MATRIX_COLUMNS - 1;
    return y;
}

void Matrix::RotatePiece(Rotation rotation) {
    if (CanRotate(rotation)) {
        EraseCurrent();
        unsigned int newOrient = GetNewOrientation(rotation);
        current->SetOrientation(newOrient);
        KeepCurrent();
    }
}
bool Matrix::CanRotate(Rotation rotation) {
    unsigned int newOrient = GetNewOrientation(rotation);
    unsigned int x = current->GetX();
    unsigned int y = current->GetY();
    EraseCurrent();
    for (unsigned int i1 = x, i2 = 0; i1 < x + NUM_BLOCKS && i2 < NUM_BLOCKS; i1++, i2++) {
        for (unsigned int j1 = y, j2 = 0; j1 < y + NUM_BLOCKS && j2 < NUM_BLOCKS; j1++, j2++) {
            if (matrix[GetInBoundsX(i1)][GetInBoundsY(j1)] != 0 && current->GetCodeAt(newOrient, i2, j2) != 0) {
                //     printf("matrix[%d][%d]=%d && tetromino[%d][%d]=%d\n", GetInBoundsX(i1), GetInBoundsY(j1), matrix[GetInBoundsX(i1)][GetInBoundsY(j1)], i2, j2, current->GetCodeAt(i2, j2));
                KeepCurrent();
                return false;
            }
        }
    }
    KeepCurrent();
    return true;
}

unsigned int Matrix::GetNewOrientation(Rotation rotation) {
    unsigned int orientation = current->GetOrientation();
    if (rotation == Rotation::CLOCKWISE)
        orientation++;
    else if (rotation == Rotation::ANTI_CLOCKWISE)
        orientation--;

    //Bounds Checking for Orientation - Has to be between 0 and 3
    if (orientation >= ORIENTATIONS)
        orientation = 0;
    else if (orientation < 0)
        orientation = ORIENTATIONS - 1;

    return orientation;
}

Matrix::~Matrix() {
}
