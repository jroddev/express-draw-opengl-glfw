
#ifndef EXPRESS_DRAW_TEXTRENDERER_H
#define EXPRESS_DRAW_TEXTRENDERER_H

#include "express-draw/TextureIdentifier.h"
#include "express-draw-opengl-glfw/font/FontLoader.h"
#include "OpenGL_GLFW_Context.h"
#include <glm/glm.hpp>
#include <express-draw/DrawTypes.h>


struct RenderableCharacter {
    Draw::Transform2D transform;
    glm::vec4 color;
    Draw::Rect textureRegion;
};

struct RenderableText {
    Draw::Transform2D transform;
    Draw::Rect boundingBox;
    Draw::TextureIdentifier texture;
    std::vector<RenderableCharacter> characters;
};

RenderableText convertToRenderableText(Draw::OpenGL_GLFW_Context& context, const Draw::TextBlock& input);

#endif //EXPRESS_DRAW_TEXTRENDERER_H
