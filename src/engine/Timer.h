#ifndef ASTEROID_DESTROYER_TIMER_H
#define ASTEROID_DESTROYER_TIMER_H


#include <chrono>
#include <thread>

class Timer {
public:
    static void setTimeout(auto function, int delay) {
        std::thread t([=]() {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay));
            function();
        });
        t.detach();
    }
};


#endif //ASTEROID_DESTROYER_TIMER_H
