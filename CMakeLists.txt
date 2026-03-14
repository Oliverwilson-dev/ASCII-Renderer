cmake_minimum_required(VERSION 3.14)
project(ascii_renderer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra)

include_directories(${CMAKE_SOURCE_DIR}/include)

set(MATH_SOURCES
    src/math/vec2.cpp
    src/math/vec3.cpp
    src/math/mat2.cpp
    src/math/mat3.cpp
)
set(FRAMEBUFFER_SOURCES src/framebuffer/framebuffer.cpp)
set(RENDERER_SOURCES src/renderer/renderer.cpp)

add_executable(ascii_renderer
    src/main.cpp
    ${MATH_SOURCES}
    ${FRAMEBUFFER_SOURCES}
    ${RENDERER_SOURCES}
)

set_target_properties(ascii_renderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

add_executable(ascii_tests
    tests/test_main.cpp
    tests/math/mathTest.cpp
    tests/renderer/rendererTest.cpp
    ${MATH_SOURCES}
    ${FRAMEBUFFER_SOURCES}
    ${RENDERER_SOURCES}
)
target_include_directories(ascii_tests PRIVATE ${CMAKE_SOURCE_DIR}/tests)
set_target_properties(ascii_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
