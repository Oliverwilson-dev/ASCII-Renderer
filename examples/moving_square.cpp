#include "renderer/renderer.h"
#include "framebuffer/framebuffer.h"
#include "math/vec2.h"
#include "math/mat3.h"
#include <iostream>
#include <cmath>
#include <chrono>
#include <thread>

using namespace ascii;

int main() {
    const std::size_t width = 50;
    const std::size_t height = 24;
    const float halfSize = 0.08f;
    const float speed = 0.015f;
    const float left = 0.15f;
    const float right = 0.85f;

    Framebuffer fb(width, height);
    Renderer renderer(fb);

    RenderState state;
    state.shapeType = ShapeType::Square;
    state.is3D = false;

    float x = left;

    while (true) {
        fb.clear(' ');
        state.transform = Mat3::translation(x, 0.5f);
        renderer.bindState(state);

        std::vector<Vertex2> square = {
            {{-halfSize, -halfSize}},
            {{ halfSize, -halfSize}},
            {{ halfSize,  halfSize}},
            {{-halfSize,  halfSize}}
        };
        renderer.draw(square);

        std::cout << fb.toString() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(80));

        x += speed;
        if (x > right)
            x = left;
        else if (x < left)
            x = right;
    }
    return 0;
}
