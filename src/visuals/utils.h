#ifndef JNP3_VS_PROJECTS_UTILS_H
#define JNP3_VS_PROJECTS_UTILS_H

namespace utils {
    template<typename Interface>
    inline void SafeRelease(Interface **ppInterfaceToRelease) {
        if (*ppInterfaceToRelease != nullptr) {
            (*ppInterfaceToRelease)->Release();
            *ppInterfaceToRelease = nullptr;
        }
    }
} // namespace utils

#endif //JNP3_VS_PROJECTS_UTILS_H
