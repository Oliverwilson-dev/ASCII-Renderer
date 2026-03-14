#pragma once

#include "vec2.h"
#include "vec3.h"

namespace ascii {

struct Mat3 {
    float m00{1.0f}, m01{0.0f}, m02{0.0f};
    float m10{0.0f}, m11{1.0f}, m12{0.0f};
    float m20{0.0f}, m21{0.0f}, m22{1.0f};

    Mat3() = default;
    Mat3(float m00, float m01, float m02,
         float m10, float m11, float m12,
         float m20, float m21, float m22);

    static Mat3 identity();
    static Mat3 translation(float x, float y);
    static Mat3 rotation(float radians);
    static Mat3 translationAndRotation(float x, float y, float radians);

    Mat3 operator*(const Mat3& other) const;
    Vec3 operator*(const Vec3& v) const;
    Vec2 transformPoint(float x, float y) const;
};

}  // namespace ascii
