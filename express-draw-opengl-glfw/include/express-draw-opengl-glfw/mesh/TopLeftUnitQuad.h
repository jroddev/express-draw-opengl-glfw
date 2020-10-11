
#ifndef EXPRESS_DRAW_TOPLEFTUNITQUAD_H
#define EXPRESS_DRAW_TOPLEFTUNITQUAD_H

#include "Vertex.h"
#include <array>

namespace TopLeftUnitQuad {
    constexpr const auto vertices = std::array<Vertex, 4>{
            // positions            // texture coords
            Vertex{.position{1.F,  1.F}, .textureCoords{1.0f, 1.0f}},   // top right
            Vertex{.position{1.F, 0.F},  .textureCoords{1.0f, 0.0f}},   // bottom right
            Vertex{.position{0.F, 0.F},  .textureCoords{0.0f, 0.0f}},   // bottom left
            Vertex{.position{0.F,  1.F}, .textureCoords{0.0f, 1.0f}}    // top left
    };
    constexpr const auto verticesIndexOffset = 0;
    constexpr const auto textureCoordIndexOffset = 2;

    constexpr const auto indices = std::array<int, 6>{
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    constexpr const auto stride = sizeof(Vertex);
}


#endif //EXPRESS_DRAW_TOPLEFTUNITQUAD_H
