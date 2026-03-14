# Renderer

The renderer is the **drawing engine**. It takes high-level commands (“draw a square with this transform”) and turns them into low-level drawing calls on a framebuffer. It does not own the framebuffer; you construct it with a reference to a `Framebuffer` and all drawing goes into that buffer.

## What it does

1. **Stores drawing state.** The renderer is a state machine. The state includes:
   - Which shape you are about to draw (triangle, square, circle, cube).
   - Whether that shape is 2D or 3D (affects which `draw()` overload and how vertices are interpreted).
   - A 2D transform (`Mat3`) applied to every vertex before it is drawn (translation, rotation).
   - For circles only: the radius (the single vertex is the center).

2. **Validates before drawing.** When you call `draw(vertices)`, the renderer checks that the number of vertices matches the current shape and that you used the right overload (2D vs 3D). If not, it throws `std::invalid_argument`. So you must set state (e.g. `bindState`) before every draw, or rely on the state you set earlier.

3. **Transforms and projects.** For each vertex, it applies the current `Mat3` transform. So vertices are in “world” or “model” space (e.g. -0.5 to 0.5); the transform moves and rotates them into the normalized 0–1 space the framebuffer expects. For 3D (cube), it only uses x and y for the screen position; z is used only for depth ordering (see below).

4. **Rasterizes shapes into lines.** It does not fill polygons; it only draws outlines:
   - **Triangle:** three lines connecting the three vertices.
   - **Square:** four lines connecting the four vertices in order.
   - **Circle:** one vertex is the center; the radius comes from state. It draws 64 short segments around the circle and one pixel at the center.
   - **Cube:** 12 edges (the standard cube edge list). It projects all 8 vertices to 2D, sorts the 12 edges by average z (depth), then draws the six “back” edges with `backChar` and the six “front” edges with `drawChar` so the cube reads as 3D.

5. **Calls into the framebuffer.** For each line or pixel, it converts normalized coordinates to pixel coordinates using the framebuffer’s `toPixelX`/`toPixelY`, then calls `framebuffer.drawLine(...)` or `setPixel(...)`. So the renderer never touches the raw buffer; it only uses the framebuffer’s public API.

## State and transforms

- **bindState(state)** — Replace the current state with the given one (shape type, is3D, transform, circle radius).
- **pushState()** / **popState()** — Save and restore state on a stack so you can temporarily change state and then restore it.
- **translate(x, y)** — Pre-multiply the current transform by a translation. So the shape moves in normalized space.
- **rotate(radians)** — Pre-multiply the current transform by a rotation around the origin. So the shape rotates around (0,0) unless you first translate to a center point.
- **resetTransform()** — Set the transform to identity.

To rotate a shape around its own center (cx, cy), set the transform to  
`T(cx, cy) * R(angle) * T(-cx, -cy)`  
before binding state and drawing (e.g. in your own code with `Mat3::translation` and `Mat3::rotation`).

## Drawing characters

- **setDrawChar(c)** — Character used for “front” lines (and all 2D shapes and the front six edges of the cube). Default `'*'`.
- **setBackChar(c)** — Character used for the six “back” edges of the cube (edges with smaller average z). Default `'.'`. Only the cube uses two characters; other shapes use only `drawChar`.

## Shape requirements

| Shape    | Vertices | Space | Notes |
|----------|----------|--------|--------|
| Triangle | 3        | 2D     | Three lines between the three points. |
| Square   | 4        | 2D     | Four lines in order (0–1–2–3–0). |
| Circle   | 1        | 2D     | That vertex is the center; radius from `state.circleRadius`. |
| Cube     | 8        | 3D     | Set `is3D = true`. Eight corners; 12 edges drawn with depth-based character. |

If you pass the wrong number of vertices or the wrong overload (e.g. 2D vertices while `is3D` is true), `draw()` throws.

## 3D and world-to-screen

For the cube, the renderer expects `Vertex3` with (x, y, z). It uses only x and y for screen position: it applies the current `Mat3` to (x, y) and ignores z for that. So the “projection” is orthographic: no perspective. The z values are used only to sort the 12 edges so that back edges are drawn with `backChar` and front edges with `drawChar`. Your code is responsible for rotating the cube in 3D and passing already-rotated vertices (and optionally projecting to 0–1 yourself); the renderer does not do 3D math beyond using z for ordering.

## API summary

| Method | Purpose |
|--------|--------|
| `Renderer(framebuffer)` | Construct; all drawing goes to this framebuffer. |
| `bindState(state)` | Set current state (shape, is3D, transform, circleRadius). |
| `state()`, `state() const` | Access or modify current state. |
| `pushState()` / `popState()` | Save / restore state. |
| `translate(x, y)` | Pre-multiply transform by translation. |
| `rotate(radians)` | Pre-multiply transform by rotation around origin. |
| `resetTransform()` | Set transform to identity. |
| `draw(vertices)` | Draw with `vector<Vertex2>` (2D) or `vector<Vertex3>` (cube). Validates count and state. |
| `setDrawChar(c)` / `setBackChar(c)` | Characters for front and back lines (cube). |

## Files

- **Header:** `include/renderer/renderer.h`
- **Implementation:** `src/renderer/renderer.cpp`

The renderer depends on the framebuffer and math (Vec2, Vec3, Mat3) headers.
