#ifndef ASTEROID_DESTROYER_UTILS_H
#define ASTEROID_DESTROYER_UTILS_H


#include <random>

namespace utils {
    thread_local static inline std::mt19937 gen{std::random_device{}()};

    template<typename T>
    T random(T min, T max) {
        return std::uniform_int_distribution<T>{min, max}(gen);
    }
} // namespace utils

#endif //ASTEROID_DESTROYER_UTILS_H
