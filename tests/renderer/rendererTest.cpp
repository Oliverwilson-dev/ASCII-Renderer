#include "renderer/rendererTest.h"
#include "renderer/renderer.h"
#include "framebuffer/framebuffer.h"
#include <cassert>
#include <stdexcept>

namespace ascii {
namespace test {

static bool runRendererTriangleTest() {
    Framebuffer fb(10, 10);
    Renderer r(fb);
    RenderState state;
    state.shapeType = ShapeType::Triangle;
    state.is3D = false;
    r.bindState(state);
    std::vector<Vertex2> tri = {
        {{0.0f, 0.0f}}, {{1.0f, 0.0f}}, {{0.5f, 1.0f}}
    };
    r.draw(tri);
    return true;
}

static bool runRendererSquareTest() {
    Framebuffer fb(10, 10);
    Renderer r(fb);
    RenderState state;
    state.shapeType = ShapeType::Square;
    state.is3D = false;
    r.bindState(state);
    std::vector<Vertex2> sq = {
        {{0.0f, 0.0f}}, {{1.0f, 0.0f}}, {{1.0f, 1.0f}}, {{0.0f, 1.0f}}
    };
    r.draw(sq);
    return true;
}

static bool runRendererCircleTest() {
    Framebuffer fb(10, 10);
    Renderer r(fb);
    RenderState state;
    state.shapeType = ShapeType::Circle;
    state.circleRadius = 0.2f;
    r.bindState(state);
    std::vector<Vertex2> circle = { {{0.5f, 0.5f}} };
    r.draw(circle);
    return true;
}

static bool runRendererValidationTest() {
    Framebuffer fb(10, 10);
    Renderer r(fb);
    RenderState state;
    state.shapeType = ShapeType::Triangle;
    r.bindState(state);
    std::vector<Vertex2> bad = { {{0.0f, 0.0f}}, {{1.0f, 0.0f}} };
    bool threw = false;
    try {
        r.draw(bad);
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    assert(threw);
    return true;
}

static bool runRendererStateStackTest() {
    Framebuffer fb(10, 10);
    Renderer r(fb);
    RenderState state;
    state.shapeType = ShapeType::Triangle;
    state.transform = Mat3::translation(0.5f, 0.5f);
    r.bindState(state);
    r.pushState();
    r.translate(0.1f, 0.1f);
    r.popState();
    assert(r.state().transform.m02 == 0.5f && r.state().transform.m12 == 0.5f);
    return true;
}

bool runRendererTests() {
    return runRendererTriangleTest() && runRendererSquareTest() &&
           runRendererCircleTest() && runRendererValidationTest() &&
           runRendererStateStackTest();
}

}
}
