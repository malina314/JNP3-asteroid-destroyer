#ifndef ASTEROID_DESTROYER_UTILS_H
#define ASTEROID_DESTROYER_UTILS_H


#include <random>
#include <type_traits>
#include <chrono>

// TODO: remove
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
//#include <errno.h>
#include <sys/types.h>
#include <string.h>

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

    // todo: remove
    static inline void logerr(const char *filename, const char *funcname, int line, const char *fmt = "", ...) {
        va_list fmt_args;

        FILE *fp = fopen("logs/log.txt", "a");

        fprintf(fp, "LOG in %s:%s:%d: ", filename, funcname, line);

        va_start(fmt_args, fmt);
        vfprintf(fp, fmt, fmt_args);
        va_end(fmt_args);

        fprintf(fp, "\n");

        fflush(fp);

        fclose(fp);

//        fprintf(stderr,"ERRNO: (%d; %s)\n", errno, strerror(errno));
    }

// todo: remove
//#define SHOULD_LOG
#ifdef SHOULD_LOG
#define LOG(...) utils::logerr(__FILE__, __func__, __LINE__ __VA_OPT__(,) __VA_ARGS__)
#else
#define LOG(...)
#endif

} // namespace utils

#endif //ASTEROID_DESTROYER_UTILS_H
