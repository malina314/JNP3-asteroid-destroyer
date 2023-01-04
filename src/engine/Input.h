#ifndef ASTEROID_DESTROYER_INPUT_H
#define ASTEROID_DESTROYER_INPUT_H


#include <cstring>

enum class Key {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SPACE,
    Count // special value used for declaring arrays
};

class Input {
    bool keyDown[static_cast<int>(Key::Count)];
    bool keyUp[static_cast<int>(Key::Count)];
    bool keyPressed[static_cast<int>(Key::Count)];

public:
    void sendKeyDown(Key key) {
        keyDown[static_cast<int>(key)] = true;
        keyPressed[static_cast<int>(key)] = true;
    }

    void sendKeyUp(Key key) {
        keyUp[static_cast<int>(key)] = true;
        keyPressed[static_cast<int>(key)] = false;
    }

    // Should be called by engine at the end of each physics update
    void update() {
        std::memset(keyDown, 0, sizeof(keyDown));
        std::memset(keyUp, 0, sizeof(keyUp));
    }

    bool isKeyPressed(Key key) const {
        return keyPressed[static_cast<int>(key)];
    }

    bool isKeyDown(Key key) const {
        return keyDown[static_cast<int>(key)];
    }
};


#endif //ASTEROID_DESTROYER_INPUT_H
