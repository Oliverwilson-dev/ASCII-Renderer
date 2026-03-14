# Math

The math sub-project provides 2D/3D vectors and 2D transforms used everywhere else: vertex positions, directions, and the renderer’s transform matrix. All types live in the `ascii` namespace and use only the C++ standard library.

## Purpose of each type

- **Vec2** — 2D positions and directions (e.g. vertex positions for triangles, squares, circles). Used by the renderer for screen-space coordinates and by you for 2D geometry.
- **Vec3** — 3D positions (e.g. cube corners). Used for 3D model space and depth; the renderer uses x,y for screen position and z for depth ordering.
- **Mat2** — 2×2 matrix for 2D rotation (and scale). No translation; rotation is around the origin.
- **Mat3** — 3×3 affine matrix for 2D: translation and rotation. Used by the renderer as the current transform; you use it to build transforms (e.g. rotate around a point).

Angles are always in **radians**.

---

## Vec2

**Files:** `include/math/vec2.h`, `src/math/vec2.cpp`

Represents a 2D vector or point with `x` and `y` (floats).

- **Constructors:** default (0,0), `Vec2(x, y)`.
- **Arithmetic:** `+`, `-`, `*` (by scalar), `+=`, `-=`.
- **Products:** `dot(other)` — scalar dot product.
- **Length:** `length()`, `normalized()` (unit vector; returns copy unchanged if length is 0).

Used for 2D vertex positions (`Vertex2.position`), 2D directions, and for the result of the renderer’s internal world-to-screen (normalized 0–1 screen position).

---

## Vec3

**Files:** `include/math/vec3.h`, `src/math/vec3.cpp`

Represents a 3D vector or point with `x`, `y`, `z` (floats).

- **Constructors:** default (0,0,0), `Vec3(x, y, z)`.
- **Arithmetic:** `+`, `-`, `*` (by scalar), `+=`, `-=`.
- **Products:** `dot(other)`, `cross(other)` (3D cross product).
- **Length:** `length()`, `normalized()`.

Used for 3D vertex positions (`Vertex3.position`), e.g. cube corners. The renderer uses x,y for screen position and z for depth when drawing the cube.

---

## Mat2

**Files:** `include/math/mat2.h`, `src/math/mat2.cpp`

Row-major 2×2 matrix with elements `m00`, `m01`, `m10`, `m11`.

- **Static:** `identity()`, `rotation(radians)` — rotation around the origin.
- **Operators:** `*` with another `Mat2` (matrix product), `*` with `Vec2` (matrix × vector).

Use when you only need 2D rotation (and possibly scale) without translation. The renderer uses `Mat3` for its state so it can support translation; you can use `Mat2` for pure rotation of directions or points if you prefer.

---

## Mat3

**Files:** `include/math/mat3.h`, `src/math/mat3.cpp`

Row-major 3×3 matrix for 2D affine transforms. Last row is (0, 0, 1) for translation; the upper-left 2×2 is rotation/scale.

- **Static:** `identity()`, `translation(x, y)`, `rotation(radians)`, `translationAndRotation(x, y, radians)` (T then R).
- **Operators:** `*` with another `Mat3`, `*` with `Vec3`.
- **Method:** `transformPoint(x, y)` — returns `Vec2`; treats (x, y) as a 2D point and applies the affine transform (for affine matrices this is the same as multiplying by (x, y, 1) and taking the first two components).

**Rotating around a point (cx, cy):**  
Build the transform as `T(cx, cy) * R(angle) * T(-cx, -cy)` so that the point (cx, cy) stays fixed and the rest of the shape rotates around it. The renderer applies whatever transform you put in `RenderState::transform` to every vertex before converting to screen space.

---

## Summary table

| Type  | Role |
|-------|------|
| Vec2  | 2D positions/directions; dot, length, normalize. |
| Vec3  | 3D positions; dot, cross, length, normalize. |
| Mat2  | 2D rotation (and scale) around origin. |
| Mat3  | 2D translation and rotation; used as the renderer’s transform. |

All types are implemented from scratch; there are no external math libraries.
