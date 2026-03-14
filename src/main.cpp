#include "renderer/renderer.h"
#include "framebuffer/framebuffer.h"
#include "math/vec3.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <chrono>
#include <thread>

using namespace ascii;

static Vec3 rotateX(const Vec3& p, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vec3(p.x, p.y * c - p.z * s, p.y * s + p.z * c);
}

static Vec3 rotateY(const Vec3& p, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vec3(p.x * c - p.z * s, p.y, p.x * s + p.z * c);
}

static Vec3 rotateZ(const Vec3& p, float angle) {
    float c = std::cos(angle);
    float s = std::sin(angle);
    return Vec3(p.x * c - p.y * s, p.x * s + p.y * c, p.z);
}

int main() {
    const std::size_t width = 50;
    const std::size_t height = 24;
    const int numCycles = 4;
    const int framesPerCycle = 16;
    const int numFrames = numCycles * framesPerCycle;
    const float twoPi = 6.283185307f;
    const float s = 0.38f;
    const float scale = 0.48f;

    const std::vector<Vec3> modelCube = {
        {-s, -s, -s}, { s, -s, -s}, { s, s, -s}, {-s, s, -s},
        {-s, -s,  s}, { s, -s,  s}, { s, s,  s}, {-s, s,  s}
    };

    Framebuffer fb(width, height);
    Renderer renderer(fb);

    RenderState state;
    state.shapeType = ShapeType::Cube;
    state.is3D = true;
    state.transform = Mat3::identity();

    renderer.setDrawChar('*');
    renderer.setBackChar('.');

    while (true) {
        for (int frame = 0; frame < numFrames; ++frame) {
            fb.clear(' ');
            float t = static_cast<float>(frame) / static_cast<float>(framesPerCycle) * twoPi;
            float angleX = t * 0.8f;
            float angleY = t * 1.0f;
            float angleZ = t * 0.6f;
            std::vector<Vertex3> cube;
            for (const Vec3& p : modelCube) {
                Vec3 r = rotateZ(rotateY(rotateX(p, angleX), angleY), angleZ);
                float u = 0.5f + scale * r.x;
                float v = 0.5f + scale * r.y;
                cube.push_back({{u, v, r.z}});
            }
            renderer.bindState(state);
            renderer.draw(cube);
            std::cout << fb.toString();
            if (frame + 1 < numFrames)
                std::cout << "\n---\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << std::endl;
    }
    return 0;
}
