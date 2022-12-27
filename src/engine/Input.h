#ifndef ASTEROID_DESTROYER_INPUT_H
#define ASTEROID_DESTROYER_INPUT_H


#include <vector>

enum class Input {
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    SHOOT
};

class InputSingleton {
public:
    std::vector<Input> inputs;

    static InputSingleton &getInstance() {
        static InputSingleton instance;

        return instance;
    }

    InputSingleton() = default;

    InputSingleton(InputSingleton const &) = delete;

    void operator=(InputSingleton const &) = delete;
};


#endif //ASTEROID_DESTROYER_INPUT_H
