#ifndef ASTEROID_DESTROYER_INPUT_H
#define ASTEROID_DESTROYER_INPUT_H


#include <vector>

enum class Input_t {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT
};

class Input {
public:
    std::vector<Input_t> inputs;
};


#endif //ASTEROID_DESTROYER_INPUT_H
