#ifndef TETRONIMO_IMPLEMENTATION_H
#define TETRONIMO_IMPLEMENTATION_H 1

#define I_FLAG 0x00

//extern const bool I_SHAPE[4][4] = {{1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}, {1, 0, 0, 0}};

class Tetronimo {
public:
    Tetronimo();
    static bool getShape() {
        return true;
    }
    ~Tetronimo();

private:
};

#endif