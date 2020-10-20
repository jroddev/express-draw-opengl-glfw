
#ifndef EXPRESS_DRAW_TEXTRENDERER_H
#define EXPRESS_DRAW_TEXTRENDERER_H

#include "express-draw/TextureIdentifier.h"
#include "express-draw-opengl-glfw/font/FontLoader.h"
#include "OpenGL_GLFW_Context.h"
#include <ranges>
#include <glm/glm.hpp>
#include <express-draw/DrawTypes.h>


struct RenderableCharacter {
    glm::vec2 position;
    glm::vec2 size;
    float rotation;
    glm::vec4 color;
    Draw::Rect textureRegion;
};

struct RenderableText {
    const TextureIdentifier texture;
    const std::vector<RenderableCharacter> characters;
};

RenderableText convertToRenderableText(Draw::OpenGL_GLFW_Context& context, const Draw::TextBlock& input);

#endif //EXPRESS_DRAW_TEXTRENDERER_H
