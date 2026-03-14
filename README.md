# ASCII Renderer

A small C++ library that draws shapes (triangles, squares, circles, cubes) into a grid of characters and outputs them as text. It uses only the C++ standard library: no graphics or math dependencies. You get wireframe shapes in the terminal with support for 2D transforms (translate, rotate) and a simple 3D cube with depth-style rendering.

## What it does

- **2D shapes:** Triangle (3 vertices), square (4 vertices), circle (center + radius). All use normalized coordinates 0–1.
- **3D cube:** 8 vertices, 12 edges; back edges and front edges can use different characters so it reads as 3D.
- **Transforms:** Translation and rotation via a stateful renderer; you set state, supply vertices, call `draw()`.
- **Output:** A `Framebuffer` holds a width×height grid of chars; you clear it, draw into it via the renderer, then call `toString()` and print (e.g. to the terminal).

Everything lives in the `ascii` namespace. See [docs/Overview.md](docs/Overview.md) for how the pieces fit together.

## Build

**Option 1: Build scripts (recommended)**

From the project root:

| Script | Unix / Linux / macOS | Windows |
|--------|----------------------|--------|
| **Build** (configure, build, run tests) | `./scripts/build/build.sh` | `scripts\build\build.bat` |
| **Clean** (remove `build/` and `bin/`) | `./scripts/build/clean.sh` | `scripts\build\clean.bat` |
| **Rebuild** (clean then build) | `./scripts/build/rebuild.sh` | `scripts\build\rebuild.bat` |

- **build** — Creates `build/` if needed, runs CMake, compiles, then runs `./bin/ascii_tests`. You can run from the repo root or from any directory; the script switches to the repo root automatically.
- **clean** — Deletes the `build/` and `bin/` directories so the next build is from scratch.
- **rebuild** — Runs clean then build. Use after changing CMake options or when the build is in a bad state.

On Unix, make the scripts executable once if needed: `chmod +x scripts/build/*.sh`

**Option 2: Manual**

From the project root:

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Binaries are produced in the project **bin** directory (e.g. `bin/` at the repo root when you run from `build/`).

## Run

**Examples:**

```bash
./bin/rotating_cube    # 3D cube rotating on X/Y/Z; Ctrl+C to stop
./bin/moving_square    # Square moving horizontally, looping
```

**Tests:**

```bash
./bin/ascii_tests
```

## Navigate the repo

| Path | Purpose |
|------|--------|
| **include/** | Public headers. `math/` (Vec2, Vec3, Mat2, Mat3), `framebuffer/`, `renderer/`. |
| **src/** | Implementation. One subfolder per area: `math/`, `framebuffer/`, `renderer/`. |
| **examples/** | Standalone programs. `rotating_cube.cpp`, `moving_square.cpp`. |
| **tests/** | Unit tests. `test_main.cpp` plus `math/mathTest.cpp`, `renderer/rendererTest.cpp`. |
| **scripts/build/** | Build scripts: `build.sh` / `build.bat`, `clean.sh` / `clean.bat`, `rebuild.sh` / `rebuild.bat`. |
| **docs/** | Detailed docs: [Overview](docs/Overview.md), [Framebuffer](docs/Framebuffer.md), [Renderer](docs/Renderer.md), [Math](docs/Math.md), [Entrypoint](docs/Entrypoint.md). |

**Where to start reading:**

- **Use the renderer** — `examples/rotating_cube.cpp` or `moving_square.cpp`: create a `Framebuffer`, create a `Renderer` with it, set `RenderState`, build vertices, call `draw()`, print `fb.toString()`.
- **Understand the pipeline** — `docs/Overview.md` and `docs/Renderer.md`.
- **Understand the buffer** — `include/framebuffer/framebuffer.h` and `docs/Framebuffer.md`.
- **Understand the math** — `include/math/*.h` and `docs/Math.md`.

**CI:** `.github/workflows/build.yml` runs on push/PR to `main` and `master`: configure, build, then run `./bin/ascii_tests`.

## Requirements

- CMake 3.25+
- C++23 compiler
- No external libraries
