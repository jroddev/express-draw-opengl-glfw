#include <express-draw-opengl-glfw/shader/Shader.h>
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include <glm/gtc/type_ptr.hpp>
#include "express-draw-opengl-glfw/mesh/UnitQuad.h"

namespace Draw {

    namespace {

        constexpr const auto vertexShader = R""""(
            #version 330 core
            layout (location = 0) in vec2 aPos;
            layout (location = 1) in vec2 aTexCoord;

            uniform mat4 model;
            uniform mat4 view;
            uniform mat4 projection;

            uniform vec4 colorTint;
            uniform vec2 textureRegionOffset;
            uniform vec2 textureRegionSize;

            out vec4 textureColorTint;
            out vec2 textureCoord;

            void main() {
                textureCoord = textureRegionOffset + (aTexCoord * textureRegionSize);
                textureColorTint = colorTint;
                gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
            }
        )"""";

        constexpr const auto fragmentShader = R""""(
            #version 330 core
            in vec2 textureCoord;
            in vec4 textureColorTint;
            uniform sampler2D textureSampler;

            out vec4 fragmentColor;

            void main() {
                vec4 textureColor = texture(textureSampler, textureCoord);
                fragmentColor = textureColor * textureColorTint;
            }
        )"""";
    }

    template<>
    void draw(OpenGL_GLFW_Context& context, const Sprite& data) {
        static const auto shader = Shader{"sprite-shader", vertexShader, fragmentShader};
        static const auto modelMatrixLocation = glGetUniformLocation(shader, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto colorLocation = glGetUniformLocation(shader, "colorTint");
        static const auto textureRegionOffsetLocation = glGetUniformLocation(shader, "textureRegionOffset");
        static const auto textureRegionSizeLocation = glGetUniformLocation(shader, "textureRegionSize");

        const auto mesh = context.quadMeshes.at(data.pivotPoint);
        const auto texture = context.getOrLoadTexture(data.texture);
        texture.bind();

        //////////////////////////

        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glUseProgram(shader);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(data.transform.getGetLocalSpaceMatrix()));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glUniform2fv(textureRegionOffsetLocation, 1, glm::value_ptr(glm::vec2{data.textureRegion.x, data.textureRegion.y}));
        glUniform2fv(textureRegionSizeLocation, 1, glm::value_ptr(glm::vec2{data.textureRegion.width, data.textureRegion.height}));
        glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
    }

}