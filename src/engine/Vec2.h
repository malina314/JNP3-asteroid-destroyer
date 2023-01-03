#ifndef ASTEROID_DESTROYER_VEC2_H
#define ASTEROID_DESTROYER_VEC2_H


#include <cmath>

class Vec2 {
public:
    int x;
    int y;

    Vec2() : x(0), y(0) {}

    Vec2(int x, int y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(const int& scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    Vec2 operator/(const int& scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    int length() const {
        return (int) std::sqrt(x * x + y * y);
    }
};


#endif //ASTEROID_DESTROYER_VEC2_H
