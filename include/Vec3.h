#ifndef VEC3_H
#define VEC3_H

#include <cmath>

struct Vec3 {
    float x, y, z;

    Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z){}

    Vec3 operator+(const Vec3& v) const {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3& v) const {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(float t) const {
        return Vec3(x * t, y * t, z * t);
    }

    float length() const {
        return sqrtf(x * x + y * y + z * z);
    }

    Vec3 normalize() const {
        float len = length();
        if (len < 0.001f) return Vec3(0, 0, 0);
        return Vec3(x / len, y / len, z / len);
    }
};

#endif // VEC3_H