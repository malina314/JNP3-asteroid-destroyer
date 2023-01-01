#include "Engine.h"

int main() {
    Engine game{};

    while (true) {
        game.update();
//        game.wait();
    }

    return 0;
}