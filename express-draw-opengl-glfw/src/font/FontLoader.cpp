#include <GL/glew.h>
#include <glm/glm.hpp>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <utility>
#include <express-draw/TextureIdentifier.h>
#include <express-draw-opengl-glfw/Texture.h>
#include "express-draw-opengl-glfw/font/FontLoader.h"

// https://learnopengl.com/In-Practice/Text-Rendering


using CharacterRange = std::pair<unsigned int, unsigned int>; // 0 -> 128

// pixel coord to [0,1] normalised texture coord within atlas
Draw::Rect getTextureRegion(const glm::ivec2 atlasSize, uint leftPixelPosition, uint rightPixelPosition, uint pixelHeight) {
    const auto a = float(leftPixelPosition) / float(atlasSize.x);
    const auto b = float(rightPixelPosition) / float(atlasSize.x);
    return {
        .x = a,
        .y = 0.F,
        .width = b - a,
        .height = float(pixelHeight) / float(atlasSize.y)
    };
}

glm::ivec2 getTextureAtlasSize(const FT_Face& face, const CharacterRange range) {
    auto textureWidth = 0u;
    auto textureHeight = 0u;

    for (auto c = range.first; c < range.second; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "WARNING::FREETYTPE:getTextureAtlasSize Failed to load Glyph for code" << c << std::endl;
            continue;
        }
        textureWidth += face->glyph->bitmap.width;
        textureHeight = std::max(textureHeight, face->glyph->bitmap.rows);
    }

    return { textureWidth, textureHeight };
}

OpenGLTexture createEmptyTextureAtlas(const glm::ivec2 atlasSize) {
    OpenGLTexture texture;
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction
    glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            atlasSize.x,
            atlasSize.y,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            nullptr // Will fill pixels later
    );
    // set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return texture;
}

OpenGLTexture buildTextureAtlas(const FT_Face& face, const CharacterRange range, const glm::ivec2 atlasSize) {
    const auto texture = createEmptyTextureAtlas(atlasSize);
    auto xOffset = 0u;
    for (auto c = range.first; c < range.second; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)){
            std::cout << "WARNING::FREETYTPE:buildTextureAtlas Failed to load Glyph for code" << c << std::endl;
            continue;
        }

        glTexSubImage2D(
                GL_TEXTURE_2D,
                0,
                xOffset,
                0,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer);
        xOffset += face->glyph->bitmap.width;
    }
    return texture;
}


Font::FontCharacterData getCharacterInfo(const FT_Face& face, const CharacterRange range, const glm::ivec2 atlasSize) {
    Font::FontCharacterData characters;
    uint xPixelPos = 0;
    for (auto c = range.first; c < range.second; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            std::cout << "WARNING::FREETYTPE:buildTextureAtlas Failed to load Glyph for code" << c << std::endl;
            continue;
        }

        const auto pixelSize = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
        const auto textureRegion = getTextureRegion(atlasSize, xPixelPos, xPixelPos + pixelSize.x, pixelSize.y);
        const auto info = Font::CharacterInfo{
            .textureRegion = textureRegion,
            .size = pixelSize,
            .bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            .advance = static_cast<unsigned int>(face->glyph->advance.x)
        };
        characters.emplace(c, info);
        xPixelPos += pixelSize.x;
    }
    return characters;
}


std::tuple<Font::FontInfo, Texture> Font::loadFromFontFile(std::string_view fontFilePath, int fontPixelSize) {
    FT_Library ft;
    if (FT_Init_FreeType(&ft)){
        std::cerr << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        throw std::runtime_error("Could not init FreeType Library");
    }

    FT_Face face;
    if (FT_New_Face(ft, fontFilePath.data(), 0, &face)){
        std::cerr << "ERROR::FREETYPE: Failed to load font" << std::endl;
        throw std::runtime_error("CFailed to load font");
    }

    // Set Font Size
    FT_Set_Pixel_Sizes(face, 0, fontPixelSize);

    const auto characterRange = CharacterRange{0,128};
    const auto textureAtlasSize = getTextureAtlasSize(face, characterRange);
    const auto textureAtlas = buildTextureAtlas(face, characterRange, textureAtlasSize);
    const auto characters = getCharacterInfo(face, characterRange, textureAtlasSize);
    std::cout << fontFilePath << ": " << textureAtlasSize.x << ", " << textureAtlasSize.y << std::endl;

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); // untested

    const auto fontInfo = FontInfo {
        .textureIdentifier{TextureIdentifier{std::string{fontFilePath} + std::to_string(fontPixelSize)}},
        .characters{characters},
        .lineHeight = fontPixelSize
    };
    const auto texture = Texture{
        textureAtlas,
        textureAtlasSize,
        1
    };
    return {
        fontInfo,
        texture
    };
}