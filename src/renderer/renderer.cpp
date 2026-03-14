#include "renderer/renderer.h"
#include <cmath>
#include <algorithm>
#include <utility>

namespace ascii {

Renderer::Renderer(Framebuffer& framebuffer) : framebuffer_(&framebuffer) {}

void Renderer::bindState(const RenderState& state) {
    state_ = state;
}

void Renderer::pushState() {
    stateStack_.push_back(state_);
}

void Renderer::popState() {
    if (!stateStack_.empty()) {
        state_ = stateStack_.back();
        stateStack_.pop_back();
    }
}

void Renderer::translate(float x, float y) {
    state_.transform = Mat3::translation(x, y) * state_.transform;
}

void Renderer::rotate(float radians) {
    state_.transform = Mat3::rotation(radians) * state_.transform;
}

void Renderer::resetTransform() {
    state_.transform = Mat3::identity();
}

Vec2 Renderer::worldToScreen(float x, float y) const {
    Vec2 p = state_.transform.transformPoint(x, y);
    return p;
}

Vec2 Renderer::worldToScreen(float x, float y, float z) const {
    (void)z;
    return worldToScreen(x, y);
}

void Renderer::drawLineInBuffer(float x0, float y0, float x1, float y1, char c) {
    int px0 = framebuffer_->toPixelX(x0);
    int py0 = framebuffer_->toPixelY(y0);
    int px1 = framebuffer_->toPixelX(x1);
    int py1 = framebuffer_->toPixelY(y1);
    framebuffer_->drawLine(px0, py0, px1, py1, c);
}

void Renderer::draw(const std::vector<Vertex2>& vertices) {
    if (state_.is3D) {
        throw std::invalid_argument("Renderer: 2D vertices supplied but state is 3D");
    }
    switch (state_.shapeType) {
        case ShapeType::Triangle:
            if (vertices.size() != 3)
                throw std::invalid_argument("Renderer: Triangle requires exactly 3 vertices");
            drawTriangle2D(vertices);
            break;
        case ShapeType::Square:
            if (vertices.size() != 4)
                throw std::invalid_argument("Renderer: Square requires exactly 4 vertices");
            drawSquare2D(vertices);
            break;
        case ShapeType::Circle:
            if (vertices.size() != 1)
                throw std::invalid_argument("Renderer: Circle requires exactly 1 vertex (center)");
            drawCircle2D(vertices);
            break;
        case ShapeType::Cube:
            throw std::invalid_argument("Renderer: Cube requires 3D vertices; use draw(vector<Vertex3>)");
    }
}

void Renderer::draw(const std::vector<Vertex3>& vertices) {
    if (!state_.is3D) {
        throw std::invalid_argument("Renderer: 3D vertices supplied but state is 2D");
    }
    if (state_.shapeType != ShapeType::Cube) {
        throw std::invalid_argument("Renderer: 3D state is for Cube only");
    }
    if (vertices.size() != 8) {
        throw std::invalid_argument("Renderer: Cube requires exactly 8 vertices");
    }
    drawCube3D(vertices);
}

void Renderer::drawTriangle2D(const std::vector<Vertex2>& vertices) {
    Vec2 a = worldToScreen(vertices[0].position.x, vertices[0].position.y);
    Vec2 b = worldToScreen(vertices[1].position.x, vertices[1].position.y);
    Vec2 c = worldToScreen(vertices[2].position.x, vertices[2].position.y);
    drawLineInBuffer(a.x, a.y, b.x, b.y, drawChar_);
    drawLineInBuffer(b.x, b.y, c.x, c.y, drawChar_);
    drawLineInBuffer(c.x, c.y, a.x, a.y, drawChar_);
}

void Renderer::drawSquare2D(const std::vector<Vertex2>& vertices) {
    for (int i = 0; i < 4; ++i) {
        int j = (i + 1) % 4;
        Vec2 a = worldToScreen(vertices[i].position.x, vertices[i].position.y);
        Vec2 b = worldToScreen(vertices[j].position.x, vertices[j].position.y);
        drawLineInBuffer(a.x, a.y, b.x, b.y, drawChar_);
    }
}

void Renderer::drawCircle2D(const std::vector<Vertex2>& vertices) {
    float cx = vertices[0].position.x;
    float cy = vertices[0].position.y;
    float r = state_.circleRadius;
    Vec2 center = worldToScreen(cx, cy);
    int centerPx = framebuffer_->toPixelX(center.x);
    int centerPy = framebuffer_->toPixelY(center.y);
    int segments = 64;
    float prevX = cx + r;
    float prevY = cy;
    Vec2 prev = worldToScreen(prevX, prevY);
    for (int i = 1; i <= segments; ++i) {
        float t = static_cast<float>(i) / static_cast<float>(segments) * 2.0f * 3.14159265f;
        float nx = cx + r * std::cos(t);
        float ny = cy + r * std::sin(t);
        Vec2 next = worldToScreen(nx, ny);
        drawLineInBuffer(prev.x, prev.y, next.x, next.y, drawChar_);
        prev = next;
    }
    framebuffer_->setPixel(static_cast<std::size_t>(std::max(0, centerPx)),
                           static_cast<std::size_t>(std::max(0, centerPy)), drawChar_);
}

void Renderer::drawCube3D(const std::vector<Vertex3>& vertices) {
    static const int edges[12][2] = {
        {0,1},{1,2},{2,3},{3,0},
        {4,5},{5,6},{6,7},{7,4},
        {0,4},{1,5},{2,6},{3,7}
    };
    std::vector<Vec2> screen(8);
    for (int i = 0; i < 8; ++i) {
        screen[i] = worldToScreen(vertices[i].position.x, vertices[i].position.y, vertices[i].position.z);
    }
    std::vector<std::pair<int, float>> edgeDepth(12);
    for (int i = 0; i < 12; ++i) {
        float z0 = vertices[edges[i][0]].position.z;
        float z1 = vertices[edges[i][1]].position.z;
        edgeDepth[i] = {i, (z0 + z1) * 0.5f};
    }
    std::sort(edgeDepth.begin(), edgeDepth.end(),
              [](const std::pair<int, float>& a, const std::pair<int, float>& b) { return a.second < b.second; });
    for (int i = 0; i < 12; ++i) {
        int e = edgeDepth[i].first;
        char c = (i < 6) ? backChar_ : drawChar_;
        drawLineInBuffer(screen[edges[e][0]].x, screen[edges[e][0]].y,
                         screen[edges[e][1]].x, screen[edges[e][1]].y, c);
    }
}

}  // namespace ascii
