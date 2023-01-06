#ifndef ASTEROID_DESTROYER_UTILS_H
#define ASTEROID_DESTROYER_UTILS_H


#include <random>
#include <type_traits>
#include <chrono>

namespace utils {
    using time_point = std::chrono::system_clock::time_point;
    using duration = std::chrono::duration<float, std::micro>;

    thread_local static inline std::mt19937 gen{std::random_device{}()};

    template<typename T>
    T random(T min, T max) {
        using dist = std::conditional_t<
                std::is_integral<T>::value,
                std::uniform_int_distribution<T>,
                std::uniform_real_distribution<T>
        >;
        return dist{min, max}(gen);
    }

    template<typename Interface>
    inline void SafeRelease(Interface **ppInterfaceToRelease) {
        if (*ppInterfaceToRelease != nullptr) {
            (*ppInterfaceToRelease)->Release();
            *ppInterfaceToRelease = nullptr;
        }
    }
} // namespace utils

#endif //ASTEROID_DESTROYER_UTILS_H
