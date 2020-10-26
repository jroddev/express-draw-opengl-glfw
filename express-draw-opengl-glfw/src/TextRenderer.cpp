#include "express-draw-opengl-glfw/TextRenderer.h"
#include <algorithm>
#include <iostream>


RenderableText convertToRenderableText(Draw::OpenGL_GLFW_Context& context, const Draw::TextBlock& input) {
    using namespace std;

    const auto fontData = context.getOrLoadFont(input.font, input.fontSize);
    float x = 0.F; // order constraint
    float y = 0.F; // order constraint
    const auto textToCharacterData = [&fontData, &x, &y, &input](auto c) -> RenderableCharacter{
        const Font::CharacterInfo cd = fontData.characters.at(c);
        const RenderableCharacter result = {
                .transform{ Draw::Transform2D::from(
                        x + cd.bearing.x,
                        y - cd.bearing.y + static_cast<float>(fontData.lineHeight),
                        0.F,
                        cd.size.x, cd.size.y
                )},
                .color {0.F, 1.F, 0.F, 1.F},
                .textureRegion = cd.textureRegion,
        };
        cout << "x before advance: " << c << " -> " << x << endl;
        x += (cd.advance >> 6); // bitshift by 6 to get value in pixels (2^6 = 64)

        // do wrap here if larger than block
        if (x > input.blockSize.x && c == ' ') {
            x = 0;
            y +=  static_cast<float>(fontData.lineHeight);
        }
        return result;
    };

    const auto characters = input.text | views::transform(textToCharacterData);
    const auto outputCharacters = std::vector<RenderableCharacter>{characters.begin(), characters.end()};
    cout << "after transform" << endl;

    const auto maxX = outputCharacters
            | views::transform([](auto a){return a.transform.position.x + a.transform.scale.x;});

    const auto maxY = outputCharacters
             | views::transform([](auto a){return a.transform.position.y + a.transform.scale.y;});

    return RenderableText {
            .transform = input.transform,
            .boundingBox = {
                    .x = 0.F,
                    .y = 0.F,
                    .width = ranges::max(maxX),
                    .height = ranges::max(maxY)
            },
            .texture = fontData.textureIdentifier,
            .characters = outputCharacters
    };
}