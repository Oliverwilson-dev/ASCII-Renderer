#pragma once

#include "vec2.h"

namespace ascii {

struct Mat2 {
    float m00{1.0f}, m01{0.0f};
    float m10{0.0f}, m11{1.0f};

    Mat2() = default;
    Mat2(float m00, float m01, float m10, float m11);

    static Mat2 identity();
    static Mat2 rotation(float radians);

    Mat2 operator*(const Mat2& other) const;
    Vec2 operator*(const Vec2& v) const;
};

}  // namespace ascii
