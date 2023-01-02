#ifndef ASTEROID_DESTROYER_UTILS_H
#define ASTEROID_DESTROYER_UTILS_H

namespace utils {
    template<typename Interface>
    inline void SafeRelease(Interface **ppInterfaceToRelease) {
        if (*ppInterfaceToRelease != nullptr) {
            (*ppInterfaceToRelease)->Release();
            *ppInterfaceToRelease = nullptr;
        }
    }
} // namespace utils

#endif //ASTEROID_DESTROYER_UTILS_H
