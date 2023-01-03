#ifndef ASTEROID_DESTROYER_SINGLETON_H
#define ASTEROID_DESTROYER_SINGLETON_H


template<typename T>
class Singleton {
public:
    static T& getInstance() {
        static T instance;
        return instance;
    }

    Singleton(const Singleton&) = delete;

    Singleton& operator=(const Singleton&) = delete;
};


#endif //ASTEROID_DESTROYER_SINGLETON_H
