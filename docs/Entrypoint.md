# Entrypoint

The application entrypoint is `main()` in `src/main.cpp`.

## Building

From the project root:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

The executable is produced at `build/bin/ascii_renderer`.

## Running

```bash
./build/bin/ascii_renderer
```

The program draws 16 frames of a square rotating around its center. Each frame is a 50×24 ASCII grid. Frames are separated by `---`.

## Running tests

```bash
./build/bin/ascii_tests
```

Tests cover the math types (Vec2, Vec3, Mat2, Mat3) and the renderer (draw calls, validation, state stack). See `tests/math/` and `tests/renderer/`.
