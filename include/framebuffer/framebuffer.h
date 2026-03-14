#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace ascii {

class Framebuffer {
public:
    Framebuffer(std::size_t width, std::size_t height);
    Framebuffer(const Framebuffer&) = default;
    Framebuffer& operator=(const Framebuffer&) = default;

    std::size_t width() const { return width_; }
    std::size_t height() const { return height_; }

    void clear(char fill = ' ');
    void setPixel(std::size_t x, std::size_t y, char c);
    char getPixel(std::size_t x, std::size_t y) const;

    void drawLine(int x0, int y0, int x1, int y1, char c = '*');

    int toPixelX(float u) const;
    int toPixelY(float v) const;

    std::string toString() const;

private:
    std::size_t width_;
    std::size_t height_;
    std::vector<char> buffer_;
};

}  // namespace ascii
