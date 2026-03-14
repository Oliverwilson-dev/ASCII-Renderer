# Renderer

The renderer draws shapes into a framebuffer using normalized coordinates (0–1 on both axes). It behaves as a state machine: you set state, then issue draw calls.

## Types

- **ShapeType:** `Triangle`, `Square`, `Circle`, `Cube`
- **Vertex2:** `Vec2 position` — for 2D shapes
- **Vertex3:** `Vec3 position` — for 3D (Cube)
- **RenderState:** `shapeType`, `is3D`, `transform` (Mat3), `circleRadius` (for Circle)

## Workflow

1. Create a `Framebuffer` and a `Renderer` that uses it.
2. Optionally `pushState()` to save the current state.
3. Build a `RenderState` (shape type, 2D/3D, transform, and for Circle the radius) and call `bindState(state)`.
4. Fill a `std::vector<Vertex2>` or `std::vector<Vertex3>` with vertices.
5. Call `draw(vertices)`. The renderer validates vertex count and throws `std::invalid_argument` if it does not match the current shape type.
6. Optionally `popState()` to restore a previously saved state.

## Transform

- **translate(x, y):** Applies translation in normalized space; equivalent to prepending `Mat3::translation(x, y)` to the current transform.
- **rotate(radians):** Applies rotation around the current origin; equivalent to prepending `Mat3::rotation(radians)`.
- **resetTransform():** Sets the transform to identity.

To rotate a shape around its center `(cx, cy)`, set  
`state.transform = Mat3::translation(cx, cy) * Mat3::rotation(angle) * Mat3::translation(-cx, -cy)`  
before binding state and drawing.

## Shape requirements

| Shape    | Vertices | Notes |
|----------|----------|--------|
| Triangle | 3        | 2D only |
| Square   | 4        | 2D only |
| Circle   | 1        | 2D; center in vertex, radius in `RenderState::circleRadius` |
| Cube     | 8        | 3D only; set `is3D = true` and pass `std::vector<Vertex3>` |

## 3D / world-to-screen

For `Cube`, the renderer uses an orthographic projection: it ignores the z component when mapping to the screen and only uses x and y. The private method `worldToScreen` performs this mapping after applying the current `Mat3` transform to the 2D part of each vertex.

## Framebuffer

- **Coordinates:** Normalized (0–1) map to the buffer: x 0→1 = left→right, y 0→1 = bottom→top in math terms; the framebuffer displays y=0 at the top.
- **Output:** Call `Framebuffer::toString()` to get a string of the current frame (e.g. for printing).
