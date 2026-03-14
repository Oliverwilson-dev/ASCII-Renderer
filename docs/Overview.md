# Overview

This project is an **ASCII renderer**: it draws shapes (triangles, squares, circles, cubes) into a grid of characters and outputs them as text. It uses only the C++ standard library and is structured into three sub-projects that work together.

## How the pieces fit together

```
┌─────────────────────────────────────────────────────────────┐
│  Your code (e.g. examples/rotating_cube.cpp)                │
│  - Sets up state (shape type, transform)                     │
│  - Supplies vertices                                         │
│  - Calls renderer.draw(vertices)                             │
└───────────────────────────┬─────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  Renderer (include/renderer/, src/renderer/)                │
│  - Interprets vertices according to current state             │
│  - Applies transform (translate/rotate)                       │
│  - Converts world coords → normalized screen coords           │
│  - Rasterizes shape (lines, circle segments)                  │
│  - Asks framebuffer to draw each line/pixel                  │
└───────────────────────────┬─────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  Framebuffer (include/framebuffer/, src/framebuffer/)         │
│  - Stores a width×height grid of chars                        │
│  - Converts normalized (0–1) coords → pixel indices           │
│  - Draws lines (parametric), sets pixels                       │
│  - Exposes toString() for terminal output                     │
└───────────────────────────┬─────────────────────────────────┘
                            │
                            ▼
┌─────────────────────────────────────────────────────────────┐
│  Math (include/math/, src/math/)                             │
│  - Vec2, Vec3: positions, directions, dot/cross/length        │
│  - Mat2, Mat3: 2D rotation and translation                    │
│  Used by the renderer and by your code for transforms.        │
└─────────────────────────────────────────────────────────────┘
```

- **Math** provides vectors and matrices. Your code and the renderer use them for positions and for 2D transforms (rotation, translation).
- **Framebuffer** is the output buffer: a 2D array of characters. It knows how to map normalized coordinates (0–1 in x and y) to pixel positions and how to draw lines in pixel space.
- **Renderer** is the drawing engine. It does not own the buffer; you give it a reference to a `Framebuffer`. It keeps a **state** (what shape, 2D vs 3D, current transform, circle radius). When you call `draw(vertices)`, it checks the state, validates vertex count, transforms vertices with the current matrix, converts to normalized screen space, then calls into the framebuffer to draw the actual lines (and for circles, many short segments).

So: **you** own the framebuffer and drive the loop (clear, set state, build vertices, draw, print). The **renderer** turns high-level “draw this shape with this state” into low-level “draw these lines in the framebuffer.” The **framebuffer** only deals with pixels and output.

## Coordinate system

- **World / logical space:** Normalized. X and Y are in the range 0–1. X increases to the right; Y increases **up** (math convention).
- **Framebuffer display:** The same 0–1 range is mapped so that (0,0) is bottom-left and (1,1) is top-right in logical terms, but when printed, the first row of text is the **top** of the screen (Y=1) and the last row is the bottom (Y=0). The framebuffer’s `toPixelY` flips Y so that logical “up” appears at the top of the terminal.

## Where to read next

- **[Framebuffer.md](Framebuffer.md)** — What the framebuffer does, pixel vs normalized coords, line drawing, and output.
- **[Renderer.md](Renderer.md)** — What the renderer does, state machine, shapes, transforms, and 3D handling.
- **[Math.md](Math.md)** — What each math type is for and how to use it.
- **[Entrypoint.md](Entrypoint.md)** — How to build, run examples, and run tests.
