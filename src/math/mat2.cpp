#include "math/mat2.h"
#include <cmath>

namespace ascii {

Mat2::Mat2(float m00, float m01, float m10, float m11)
    : m00(m00), m01(m01), m10(m10), m11(m11) {}

Mat2 Mat2::identity() {
    return Mat2(1, 0, 0, 1);
}

Mat2 Mat2::rotation(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);
    return Mat2(c, -s, s, c);
}

Mat2 Mat2::operator*(const Mat2& other) const {
    return Mat2(
        m00 * other.m00 + m01 * other.m10, m00 * other.m01 + m01 * other.m11,
        m10 * other.m00 + m11 * other.m10, m10 * other.m01 + m11 * other.m11
    );
}

Vec2 Mat2::operator*(const Vec2& v) const {
    return Vec2(m00 * v.x + m01 * v.y, m10 * v.x + m11 * v.y);
}

}  // namespace ascii
