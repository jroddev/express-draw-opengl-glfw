#ifndef EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H
#define EXPRESS_DRAW_OPENGL_GLFW__FONTLOADER_H

#include <unordered_map>
#include <glm/glm.hpp>
#include <memory>

namespace Font {

    struct CharacterInfo {
        float textureLeft;  // left coord inside texture atlas
        float textureRight; // right coord inside texture atlas
        glm::ivec2 size;        // size of glyph in pixels
        glm::ivec2 bearing;     // offset from baseline to left/top of glyph
        unsigned int advance;   // offset to advance to next glyph
    };

    using FontCharacterData = std::unordered_map<char, CharacterInfo>;
    struct FontInfo {
        std::string name;
        TextureIdentifier textureIdentifier;
        FontCharacterData characters;
    };

    std::tuple<Font::FontInfo, Texture> loadFromFontFile(std::string_view fontFilePath, std::string name, int fontPixelSize = 48);
}
#endif
