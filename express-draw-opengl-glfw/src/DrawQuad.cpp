#include <express-draw-opengl-glfw/shader/Shader.h>
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include <glm/gtc/type_ptr.hpp>
#include "express-draw-opengl-glfw/mesh/TopLeftUnitQuad.h"

namespace Draw {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform mat4 view;
        uniform mat4 projection;
        uniform vec2 position;
        uniform vec2 size;
        uniform vec4 color;

        out vec4 outputColor;

        void main() {
            outputColor = color;
            float x = position.x + (aPos.x * size.x);
            float y = position.y + (aPos.y * size.y);
            vec4 worldSpacePosition = vec4(x, y, 0, 1);
            gl_Position = projection * view * worldSpacePosition;
        }
    )"""";

        constexpr const auto fragmentShader = R""""(
        #version 330 core
        in vec4 outputColor;
        out vec4 fragmentColor;

        void main() {
            fragmentColor = outputColor;
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

    template<>
    void draw(OpenGL_GLFW_Context& context, Quad data) {
        static const auto shader = Shader{"wireframe-shader", vertexShader, fragmentShader};
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto positionLocation = glGetUniformLocation(shader, "position");
        static const auto sizeLocation = glGetUniformLocation(shader, "size");
        static const auto colorLocation = glGetUniformLocation(shader, "color");
        static const auto mesh = buildMesh();

        //////////////////////////

        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glUseProgram(shader);
        glLineWidth(data.borderWidth);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform2fv(positionLocation, 1, glm::value_ptr(data.position));
        glUniform2fv(sizeLocation, 1, glm::value_ptr(data.size));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
    }

    template<>
    void drawWireframe(OpenGL_GLFW_Context& context, Quad data) {
        static const auto shader = Shader{"wireframe-shader", vertexShader, fragmentShader};
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto positionLocation = glGetUniformLocation(shader, "position");
        static const auto sizeLocation = glGetUniformLocation(shader, "size");
        static const auto colorLocation = glGetUniformLocation(shader, "color");
        static const auto mesh = buildMesh();

        //////////////////////////

        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glUseProgram(shader);
        glLineWidth(data.borderWidth);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform2fv(positionLocation, 1, glm::value_ptr(data.position));
        glUniform2fv(sizeLocation, 1, glm::value_ptr(data.size));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}