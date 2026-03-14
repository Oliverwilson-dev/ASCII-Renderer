# Math

The project defines four math types in the `ascii` namespace: `Vec2`, `Vec3`, `Mat2`, and `Mat3`. All are implemented from scratch using only the C++ standard library.

## Vec2

- **Headers:** `include/math/vec2.h`, `src/math/vec2.cpp`
- **Fields:** `x`, `y` (float)
- **Constructors:** default, `Vec2(float x, float y)`
- **Operators:** `+`, `-`, `*` (scalar), `+=`, `-=`
- **Methods:** `dot(Vec2)`, `length()`, `normalized()`

## Vec3

- **Headers:** `include/math/vec3.h`, `src/math/vec3.cpp`
- **Fields:** `x`, `y`, `z` (float)
- **Constructors:** default, `Vec3(float x, float y, float z)`
- **Operators:** `+`, `-`, `*` (scalar), `+=`, `-=`
- **Methods:** `dot(Vec3)`, `cross(Vec3)`, `length()`, `normalized()`

## Mat2

- **Headers:** `include/math/mat2.h`, `src/math/mat2.cpp`
- **Layout:** row-major 2×2 (`m00`, `m01`, `m10`, `m11`)
- **Static methods:** `identity()`, `rotation(float radians)`
- **Operators:** `*` with `Mat2` and with `Vec2` (matrix × vector)

Used for 2D rotation (and scale). No translation; use `Mat3` for translation.

## Mat3

- **Headers:** `include/math/mat3.h`, `src/math/mat3.cpp`
- **Layout:** row-major 3×3 (`m00`…`m22`)
- **Static methods:** `identity()`, `translation(float x, float y)`, `rotation(float radians)`, `translationAndRotation(float x, float y, float radians)`
- **Operators:** `*` with `Mat3` and with `Vec3`
- **Methods:** `transformPoint(float x, float y)` → `Vec2` (affine transform of a 2D point)

Used for 2D transforms: translation, rotation, and combined translation+rotation. Rotation is around the origin; to rotate around a point `(cx, cy)` use:

`T(cx, cy) * R(angle) * T(-cx, -cy)`.

All angles are in radians.
