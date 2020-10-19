

#include <express-draw-opengl-glfw/OpenGL_GLFW_Context.h>
#include <express-draw/DrawTypes.h>
#include "express-draw/Draw.h"

namespace {

    constexpr const auto vertexShader = R""""(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        layout (location = 1) in vec2 aTexCoord;

        uniform mat4 view;
        uniform mat4 projection;
        uniform vec2 position;
        uniform vec2 size;
        uniform vec4 colorTint;

        out vec4 textureColorTint;
        out vec2 textureCoord;

        void main() {
            textureCoord = aTexCoord;
            textureColorTint = colorTint;

            float x = position.x + (aPos.x * size.x);
            float y = position.y + (aPos.y * size.y);
            vec4 worldSpacePosition = vec4(x, y, 0, 1);
            gl_Position = projection * view * worldSpacePosition;
        }
    )"""";

    constexpr const auto fragmentShader = R""""(
        #version 330 core
        out vec4 FragColor;

        uniform sampler2D ourTexture;
        in vec2 texCoord;

        void main() {
            float alpha = texture(ourTexture, texCoord).r;
            FragColor = vec4(0.0, 0.0, 0.0, alpha);
        }
    )"""";

}

namespace Draw {
    template<>
    void draw(OpenGL_GLFW_Context &context, Text data) {


    }
}