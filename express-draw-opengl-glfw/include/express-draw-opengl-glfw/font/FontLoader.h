#ifndef EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H
#define EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>
#include "express-draw/Common.h"
#include "express-draw-opengl-glfw/Texture.h"


namespace Font {

    struct CharacterInfo {
        Draw::Rect textureRegion;
        glm::ivec2 size;        // size of glyph in pixels
        glm::ivec2 bearing;     // offset from baseline to left/top of glyph
        unsigned int advance;   // offset to advance to next glyph
    };

    using FontCharacterData = std::unordered_map<char, CharacterInfo>;
    struct FontInfo {
        TextureIdentifier textureIdentifier;
        FontCharacterData characters;
    };

    std::tuple<Font::FontInfo, Texture> loadFromFontFile(std::string_view fontFilePath, int fontPixelSize = 48);
}
#endif
