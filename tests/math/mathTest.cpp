#include "math/mathTest.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/mat2.h"
#include "math/mat3.h"
#include <cmath>
#include <cassert>

namespace ascii {
namespace test {

static const float kEpsilon = 1e-5f;

static bool floatNear(float a, float b) {
    return std::abs(a - b) < kEpsilon;
}

static bool runVec2Tests() {
    Vec2 a(1.0f, 0.0f);
    Vec2 b(0.0f, 1.0f);
    assert(floatNear((a + b).x, 1.0f) && floatNear((a + b).y, 1.0f));
    assert(floatNear((a - b).x, 1.0f) && floatNear((a - b).y, -1.0f));
    assert(floatNear(a.dot(b), 0.0f));
    assert(floatNear(a.dot(a), 1.0f));
    assert(floatNear(a.length(), 1.0f));
    Vec2 c = a * 2.0f;
    assert(floatNear(c.x, 2.0f) && floatNear(c.y, 0.0f));
    return true;
}

static bool runVec3Tests() {
    Vec3 a(1.0f, 0.0f, 0.0f);
    Vec3 b(0.0f, 1.0f, 0.0f);
    Vec3 c = a.cross(b);
    assert(floatNear(c.x, 0.0f) && floatNear(c.y, 0.0f) && floatNear(c.z, 1.0f));
    assert(floatNear(a.dot(b), 0.0f));
    assert(floatNear(a.length(), 1.0f));
    return true;
}

static bool runMat2Tests() {
    Mat2 r = Mat2::rotation(0.0f);
    assert(floatNear(r.m00, 1.0f) && floatNear(r.m11, 1.0f) && floatNear(r.m01, 0.0f) && floatNear(r.m10, 0.0f));
    float halfPi = 1.57079632679f;
    Mat2 r90 = Mat2::rotation(halfPi);
    Vec2 v(1.0f, 0.0f);
    Vec2 w = r90 * v;
    assert(floatNear(w.x, 0.0f) && floatNear(w.y, 1.0f));
    return true;
}

static bool runMat3Tests() {
    Mat3 t = Mat3::translation(2.0f, 3.0f);
    Vec2 p = t.transformPoint(0.0f, 0.0f);
    assert(floatNear(p.x, 2.0f) && floatNear(p.y, 3.0f));
    Mat3 r = Mat3::rotation(0.0f);
    Vec2 q = r.transformPoint(1.0f, 0.0f);
    assert(floatNear(q.x, 1.0f) && floatNear(q.y, 0.0f));
    float halfPi = 1.57079632679f;
    Mat3 r90 = Mat3::rotation(halfPi);
    Vec2 u = r90.transformPoint(1.0f, 0.0f);
    assert(floatNear(u.x, 0.0f) && floatNear(u.y, 1.0f));
    Mat3 tr = Mat3::translation(0.5f, 0.5f) * Mat3::rotation(halfPi) * Mat3::translation(-0.5f, -0.5f);
    Vec2 center = tr.transformPoint(0.5f, 0.5f);
    assert(floatNear(center.x, 0.5f) && floatNear(center.y, 0.5f));
    return true;
}

bool runMathTests() {
    return runVec2Tests() && runVec3Tests() && runMat2Tests() && runMat3Tests();
}

}
}
