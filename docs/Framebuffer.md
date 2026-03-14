# Framebuffer

The framebuffer is the **output buffer** of the ASCII renderer. It holds a rectangular grid of characters (e.g. 50×24) and provides the only place where “draw something at this position” actually changes visible output.

## What it does

- **Stores one frame.** A `Framebuffer` has a fixed width and height. Internally it keeps a `std::vector<char>` of size `width × height`. Row 0 is the **top** row when you print the buffer; row `height-1` is the bottom.
- **Maps normalized coords to pixels.** The rest of the system works in normalized coordinates: x and y in the range [0, 1]. The framebuffer converts that to pixel indices:
  - `toPixelX(u)`: u=0 → left column, u=1 → right column. Result is clamped to [0, width-1].
  - `toPixelY(v)`: v=0 → bottom row, v=1 → top row. So v is “up” in math terms; the buffer flips it so that v=1 becomes row 0 (top of screen).
- **Draws primitives in pixel space.** It can set a single pixel (`setPixel(x, y, c)`) or a line between two pixel positions (`drawLine(x0, y0, x1, y1, c)`). Line drawing uses a parametric approach: step along the longer axis and round to the nearest pixel so every line is continuous.
- **Produces text output.** `toString()` walks the grid row by row and returns a single string with newlines between rows, ready to print to the terminal.

The renderer never touches the buffer directly; it calls `toPixelX`/`toPixelY` and `drawLine`/`setPixel` on the framebuffer you gave it. So the framebuffer is the only component that knows about “pixels” and “rows”; the renderer only talks in normalized (0–1) coordinates.

## API summary

| Method | Purpose |
|--------|--------|
| `Framebuffer(width, height)` | Create a buffer of the given size; initially filled with spaces. |
| `clear(char fill)` | Fill the entire buffer with `fill` (default `' '`). |
| `setPixel(x, y, c)` | Set the character at pixel (x, y). Bounds-checked; out-of-range is ignored. |
| `getPixel(x, y)` | Return the character at (x, y), or `' '` if out of range. |
| `drawLine(x0, y0, x1, y1, c)` | Draw a line in **pixel** coordinates from (x0,y0) to (x1,y1) with character `c`. |
| `toPixelX(u)` | Convert normalized x `u` in [0,1] to a pixel column index. |
| `toPixelY(v)` | Convert normalized y `v` in [0,1] to a pixel row index (v=1 → top row). |
| `toString()` | Return the whole buffer as one string (rows separated by `\n`). |

## Files

- **Header:** `include/framebuffer/framebuffer.h`
- **Implementation:** `src/framebuffer/framebuffer.cpp`

## Typical use

You create one framebuffer per “screen” or output size. Each frame you call `clear()`, then the renderer draws into it via its reference. When the frame is ready, you call `toString()` and print the result (e.g. to `std::cout`). The renderer is responsible for converting shapes and transforms into calls to the framebuffer’s `toPixelX`, `toPixelY`, and `drawLine`/`setPixel`.
