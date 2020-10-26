#include <express-draw-opengl-glfw/OpenGL_GLFW_Context.h>
#include <express-draw-opengl-glfw/mesh/UnitQuad.h>
#include <express-draw-opengl-glfw/shader/Shader.h>
#include "express-draw/Draw.h"
#include <glm/gtc/type_ptr.hpp>
#include <express-draw-opengl-glfw/TextRenderer.h>

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
            float alpha = texture(textureSampler, textureCoord).r;
            fragmentColor = textureColorTint;
            fragmentColor.a = alpha;
        }
    )"""";


    struct MeshProperties {
        GLuint vao, vbo, ebo;
        int indicesSize;
    };

    MeshProperties buildMesh() {
        GLuint vao;
        glGenVertexArrays(1, &vao); // glDeleteVertexArrays
        glBindVertexArray(vao);

        GLuint vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(
                GL_ARRAY_BUFFER,
                sizeof(TopLeftUnitQuad::vertices),
                TopLeftUnitQuad::vertices.data(),
                GL_STATIC_DRAW);

        GLuint ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(
                GL_ELEMENT_ARRAY_BUFFER,
                sizeof(TopLeftUnitQuad::indices),
                TopLeftUnitQuad::indices.data(),
                GL_STATIC_DRAW);

        glVertexAttribPointer(
                0,
                2,
                GL_FLOAT,
                GL_FALSE,
                TopLeftUnitQuad::stride,
                (void*) nullptr);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(
                1,
                2,
                GL_FLOAT, GL_FALSE,
                TopLeftUnitQuad::stride,
                (void*)(TopLeftUnitQuad::textureCoordIndexOffset * sizeof(float)));
        glEnableVertexAttribArray(1);


        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        return {
                .vao = vao,
                .vbo = vbo,
                .ebo = ebo,
                .indicesSize = TopLeftUnitQuad::indices.size()
        };
    }
}

namespace Draw {
    template<>
    void draw(OpenGL_GLFW_Context &context, const RenderableText& data) {
        static const auto shader = Shader{"text-shader", vertexShader, fragmentShader};
        static const auto modelMatrixLocation = glGetUniformLocation(shader, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto colorLocation = glGetUniformLocation(shader, "colorTint");
        static const auto textureRegionOffsetLocation = glGetUniformLocation(shader, "textureRegionOffset");
        static const auto textureRegionSizeLocation = glGetUniformLocation(shader, "textureRegionSize");

        if (data.characters.empty()){
            return;
        }

        const auto mesh = context.quadMeshes.at(PIVOT_POINT::TOP_LEFT);
        const auto texture = context.textures.at(data.texture);
        texture.bind();

        //////////////////////////
        for (const auto character: data.characters) {
            glBindVertexArray(mesh.vao);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
            glUseProgram(shader);
            glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(
                    data.transform.getGetLocalSpaceMatrix() * character.transform.getGetLocalSpaceMatrix()
                    ));
            glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
            glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
            glUniform4fv(colorLocation, 1, glm::value_ptr(character.color));
            glUniform2fv(textureRegionOffsetLocation, 1, glm::value_ptr(glm::vec2{character.textureRegion.x, character.textureRegion.y}));
            glUniform2fv(textureRegionSizeLocation, 1, glm::value_ptr(glm::vec2{character.textureRegion.width, character.textureRegion.height}));


            glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
        }

    }
}