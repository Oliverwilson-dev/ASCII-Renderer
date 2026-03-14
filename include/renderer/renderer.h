#pragma once

#include "framebuffer/framebuffer.h"
#include "math/vec2.h"
#include "math/vec3.h"
#include "math/mat3.h"
#include <vector>
#include <stdexcept>

namespace ascii {

enum class ShapeType {
    Triangle,
    Square,
    Circle,
    Cube
};

struct Vertex2 {
    Vec2 position;
};

struct Vertex3 {
    Vec3 position;
};

struct RenderState {
    ShapeType shapeType{ShapeType::Triangle};
    bool is3D{false};
    Mat3 transform{Mat3::identity()};
    float circleRadius{0.1f};
};

class Renderer {
public:
    explicit Renderer(Framebuffer& framebuffer);

    void bindState(const RenderState& state);
    const RenderState& state() const { return state_; }
    RenderState& state() { return state_; }

    void pushState();
    void popState();

    void translate(float x, float y);
    void rotate(float radians);
    void resetTransform();

    void draw(const std::vector<Vertex2>& vertices);
    void draw(const std::vector<Vertex3>& vertices);

    void setDrawChar(char c) { drawChar_ = c; }
    void setBackChar(char c) { backChar_ = c; }

private:
    Vec2 worldToScreen(float x, float y) const;
    Vec2 worldToScreen(float x, float y, float z) const;

    void drawTriangle2D(const std::vector<Vertex2>& vertices);
    void drawSquare2D(const std::vector<Vertex2>& vertices);
    void drawCircle2D(const std::vector<Vertex2>& vertices);
    void drawCube3D(const std::vector<Vertex3>& vertices);

    void drawLineInBuffer(float x0, float y0, float x1, float y1, char c = '*');

    Framebuffer* framebuffer_;
    RenderState state_;
    std::vector<RenderState> stateStack_;
    char drawChar_{'*'};
    char backChar_{'.'};
};

}  // namespace ascii
