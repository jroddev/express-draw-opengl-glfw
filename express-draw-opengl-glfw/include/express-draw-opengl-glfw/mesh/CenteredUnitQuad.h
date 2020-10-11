
#ifndef EXPRESS_DRAW_CENTEREDUNITQUAD_H
#define EXPRESS_DRAW_CENTEREDUNITQUAD_H

#include "Vertex.h"
#include <array>

namespace CenteredUnitQuad {
    constexpr const auto vertices = std::array<Vertex, 4>{
    // positions            // texture coords
    Vertex{{0.5F,  0.5F},      {1.0F, 1.0F}},   // top right
    Vertex{{0.5F, -0.5F},      {1.0F, 0.0F}},   // bottom right
    Vertex{{-0.5F, -0.5F},     {0.0F, 0.0F}},   // bottom left
    Vertex{{-0.5F,  0.5F},     {0.0F, 1.0F}}    // top left
    };
    constexpr const auto verticesIndexOffset = 0;
    constexpr const auto textureCoordIndexOffset = 3;

    constexpr const auto indices = std::array<int, 6>{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    constexpr const auto stride = sizeof(Vertex);
}

#endif //EXPRESS_DRAW_CENTEREDUNITQUAD_H
