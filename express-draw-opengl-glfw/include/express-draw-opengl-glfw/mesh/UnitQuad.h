
#ifndef EXPRESS_DRAW_CENTEREDUNITQUAD_H
#define EXPRESS_DRAW_CENTEREDUNITQUAD_H

#include "Vertex.h"
#include <array>
#include <ranges>

namespace CenteredUnitQuad {
    constexpr const auto vertices = std::array<Vertex, 4>{
    // positions            // texture coords
    Vertex{{0.5F,  0.5F},      {1.0F, 1.0F}},   // top right
    Vertex{{0.5F, -0.5F},      {1.0F, 0.0F}},   // bottom right
    Vertex{{-0.5F, -0.5F},     {0.0F, 0.0F}},   // bottom left
    Vertex{{-0.5F,  0.5F},     {0.0F, 1.0F}}    // top left
    };
    constexpr const auto verticesIndexOffset = 0;
    constexpr const auto textureCoordIndexOffset = 2;

    constexpr const auto indices = std::array<int, 6>{
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
    };

    constexpr const auto stride = sizeof(Vertex);
}

namespace {
    constexpr std::array<Vertex, 4> calculateFromCentered(const glm::vec2 offset) {
        const auto convert = [&offset](Vertex in) constexpr -> Vertex {
            return Vertex{
                    .position = {
                            in.position.x + offset.x,
                            in.position.y + offset.y
                    },
                    .textureCoords = in.textureCoords
            };
        };

        auto output = std::array<Vertex, 4>{};
        std::transform(CenteredUnitQuad::vertices.begin(), CenteredUnitQuad::vertices.end(), output.begin(), convert);
       return output;
    }
}

namespace TopLeftUnitQuad {
    constexpr const auto vertices = calculateFromCentered(glm::vec2{0.5F, 0.5F});
    constexpr const auto indices = CenteredUnitQuad::indices;
    constexpr const auto stride = CenteredUnitQuad::stride;
    constexpr const auto textureCoordIndexOffset = CenteredUnitQuad::textureCoordIndexOffset;
}

namespace TopRightUnitQuad {
    constexpr const auto vertices = calculateFromCentered( glm::vec2{-0.5F, 0.5F});
    constexpr const auto indices = CenteredUnitQuad::indices;
    constexpr const auto stride = CenteredUnitQuad::stride;
    constexpr const auto textureCoordIndexOffset = CenteredUnitQuad::textureCoordIndexOffset;
}
namespace BottomLeftUnitQuad {
    constexpr const auto vertices = calculateFromCentered(glm::vec2{0.5F, -0.5F});
    constexpr const auto indices = CenteredUnitQuad::indices;
    constexpr const auto stride = CenteredUnitQuad::stride;
    constexpr const auto textureCoordIndexOffset = CenteredUnitQuad::textureCoordIndexOffset;
}
namespace BottomRightUnitQuad {
    constexpr const auto vertices = calculateFromCentered(glm::vec2{-0.5F, -0.5F});
    constexpr const auto indices = CenteredUnitQuad::indices;
    constexpr const auto stride = CenteredUnitQuad::stride;
    constexpr const auto textureCoordIndexOffset = CenteredUnitQuad::textureCoordIndexOffset;
}



#endif //EXPRESS_DRAW_CENTEREDUNITQUAD_H
