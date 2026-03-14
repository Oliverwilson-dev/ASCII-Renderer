#include "framebuffer/framebuffer.h"
#include <cmath>
#include <sstream>
#include <algorithm>

namespace ascii {

Framebuffer::Framebuffer(std::size_t width, std::size_t height)
    : width_(width), height_(height), buffer_(width * height, ' ') {}

void Framebuffer::clear(char fill) {
    std::fill(buffer_.begin(), buffer_.end(), fill);
}

void Framebuffer::setPixel(std::size_t x, std::size_t y, char c) {
    if (x < width_ && y < height_)
        buffer_[y * width_ + x] = c;
}

char Framebuffer::getPixel(std::size_t x, std::size_t y) const {
    if (x < width_ && y < height_)
        return buffer_[y * width_ + x];
    return ' ';
}

void Framebuffer::drawLine(int x0, int y0, int x1, int y1, char c) {
    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = std::max(std::abs(dx), std::abs(dy));
    if (steps == 0) {
        setPixel(static_cast<std::size_t>(std::max(0, x0)),
                 static_cast<std::size_t>(std::max(0, y0)), c);
        return;
    }
    float incX = static_cast<float>(dx) / static_cast<float>(steps);
    float incY = static_cast<float>(dy) / static_cast<float>(steps);
    float x = static_cast<float>(x0);
    float y = static_cast<float>(y0);
    for (int i = 0; i <= steps; ++i) {
        int px = static_cast<int>(std::round(x));
        int py = static_cast<int>(std::round(y));
        setPixel(static_cast<std::size_t>(std::max(0, px)),
                 static_cast<std::size_t>(std::max(0, py)), c);
        x += incX;
        y += incY;
    }
}

int Framebuffer::toPixelX(float u) const {
    int x = static_cast<int>(std::round(u * static_cast<float>(width_ - 1)));
    return std::max(0, std::min(x, static_cast<int>(width_) - 1));
}

int Framebuffer::toPixelY(float v) const {
    int y = static_cast<int>(std::round((1.0f - v) * static_cast<float>(height_ - 1)));
    return std::max(0, std::min(y, static_cast<int>(height_) - 1));
}

std::string Framebuffer::toString() const {
    std::ostringstream out;
    for (std::size_t y = 0; y < height_; ++y) {
        for (std::size_t x = 0; x < width_; ++x)
            out << buffer_[y * width_ + x];
        if (y + 1 < height_) out << '\n';
    }
    return out.str();
}

}  // namespace ascii
