#include "math/mat3.h"
#include <cmath>

namespace ascii {

Mat3::Mat3(float m00, float m01, float m02,
           float m10, float m11, float m12,
           float m20, float m21, float m22)
    : m00(m00), m01(m01), m02(m02)
    , m10(m10), m11(m11), m12(m12)
    , m20(m20), m21(m21), m22(m22) {}

Mat3 Mat3::identity() {
    return Mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
}

Mat3 Mat3::translation(float x, float y) {
    Mat3 m = identity();
    m.m02 = x;
    m.m12 = y;
    return m;
}

Mat3 Mat3::rotation(float radians) {
    float c = std::cos(radians);
    float s = std::sin(radians);
    return Mat3(c, -s, 0, s, c, 0, 0, 0, 1);
}

Mat3 Mat3::translationAndRotation(float x, float y, float radians) {
    return translation(x, y) * rotation(radians);
}

Mat3 Mat3::operator*(const Mat3& other) const {
    return Mat3(
        m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
        m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
        m00 * other.m02 + m01 * other.m12 + m02 * other.m22,
        m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
        m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
        m10 * other.m02 + m11 * other.m12 + m12 * other.m22,
        m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
        m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
        m20 * other.m02 + m21 * other.m12 + m22 * other.m22
    );
}

Vec3 Mat3::operator*(const Vec3& v) const {
    return Vec3(
        m00 * v.x + m01 * v.y + m02 * v.z,
        m10 * v.x + m11 * v.y + m12 * v.z,
        m20 * v.x + m21 * v.y + m22 * v.z
    );
}

Vec2 Mat3::transformPoint(float x, float y) const {
    float w = m20 * x + m21 * y + m22;
    if (std::abs(w) < 1e-9f) w = 1.0f;
    return Vec2(
        (m00 * x + m01 * y + m02) / w,
        (m10 * x + m11 * y + m12) / w
    );
}

}  // namespace ascii
