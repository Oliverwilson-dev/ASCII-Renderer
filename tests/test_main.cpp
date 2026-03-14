#include "math/mathTest.h"
#include "renderer/rendererTest.h"
#include <iostream>
#include <cstdlib>

int main() {
    bool ok = true;
    if (!ascii::test::runMathTests()) {
        std::cerr << "Math tests failed.\n";
        ok = false;
    }
    if (!ascii::test::runRendererTests()) {
        std::cerr << "Renderer tests failed.\n";
        ok = false;
    }
    if (ok)
        std::cout << "All tests passed.\n";
    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
