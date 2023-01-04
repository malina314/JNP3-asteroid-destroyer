#ifndef ASTEROID_DESTROYER_VEC2_H
#define ASTEROID_DESTROYER_VEC2_H


#include <cmath>

class Vec2 {
public:
    float x;
    float y;

    Vec2() : x(0), y(0) {}

    Vec2(float x, float y) : x(x), y(y) {}

    Vec2 operator+(const Vec2& other) const {
        return Vec2(x + other.x, y + other.y);
    }

    Vec2 operator-(const Vec2& other) const {
        return Vec2(x - other.x, y - other.y);
    }

    Vec2 operator*(float scalar) const {
        return Vec2(x * scalar, y * scalar);
    }

    Vec2 operator/(float scalar) const {
        return Vec2(x / scalar, y / scalar);
    }

    Vec2 &operator+=(const Vec2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 &operator-=(const Vec2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    float length() const {
        return std::sqrt(x * x + y * y);
    }
};


#endif //ASTEROID_DESTROYER_VEC2_H
