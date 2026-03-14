# Build, run, and test

This project has no single “main” executable. It builds **examples** and a **test** executable.

## Building

From the project root:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Binaries are written to the project’s **bin** directory (e.g. `../bin` when building from `build/`), not into `build/`. So after building you get:

- `bin/rotating_cube` — rotating 3D cube (multiple axes, depth-style back/front edges).
- `bin/moving_square` — square moving slowly horizontally, looping.
- `bin/ascii_tests` — unit tests for math and renderer.

## Running examples

From the project root:

```bash
./bin/rotating_cube
```

Runs until you stop it (e.g. Ctrl+C). Each frame is a 50×24 ASCII grid; 0.1 s sleep between frames.

```bash
./bin/moving_square
```

Square moves left-to-right and wraps; 80 ms between frames.

## Running tests

```bash
./bin/ascii_tests
```

Runs all tests and prints “All tests passed.” or errors. Tests cover:

- **Math** (`tests/math/`): Vec2/Vec3 (add, dot, length, cross), Mat2/Mat3 (identity, rotation, translation, transform).
- **Renderer** (`tests/renderer/`): drawing triangle, square, circle; validation (wrong vertex count throws); state push/pop.

## Project layout

- **include/** — Public headers (math, framebuffer, renderer).
- **src/** — Implementation (.cpp) for math, framebuffer, renderer.
- **examples/** — Example programs (rotating_cube, moving_square).
- **tests/** — Test runner and test sources.
- **docs/** — Documentation (this file, Overview, Framebuffer, Renderer, Math).

For more detail on what each sub-project does, see [Overview.md](Overview.md), [Framebuffer.md](Framebuffer.md), [Renderer.md](Renderer.md), and [Math.md](Math.md).
