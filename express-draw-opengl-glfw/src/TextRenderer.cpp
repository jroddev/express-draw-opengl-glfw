#include "express-draw-opengl-glfw/TextRenderer.h"


RenderableText convertToRenderableText(Draw::OpenGL_GLFW_Context& context, const Draw::TextBlock& input) {

    const auto fontData = context.getOrLoadFont(input.font, 48);
    float x = 0.F;
    float y = 0.F; // order constraint
    static const auto textToCharacterData = [&fontData, &x, &y, &input](auto c)->RenderableCharacter{
        const Font::CharacterInfo cd = fontData.characters.at(c);
        const RenderableCharacter result = {
                .position {
                        x + cd.bearing.x,
                        y - cd.bearing.y + fontData.lineHeight
                },
                .size{cd.size.x, cd.size.y},
                .rotation = 0.F,
                .color {0.F, 1.F, 0.F, 1.F},
                .textureRegion = cd.textureRegion,
        };
        x += (cd.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)
        // do wrap here if larger than block
        if (x > input.blockSize.x && c == ' ') {
            x = 0;
            y += fontData.lineHeight;
        }
        return result;
    };

    const auto characters = input.text | std::views::transform(textToCharacterData);

    return RenderableText {
            .texture = fontData.textureIdentifier,
            .characters = {characters.begin(), characters.end()}
    };
}