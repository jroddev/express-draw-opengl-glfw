#include <express-draw-opengl-glfw/shader/Shader.h>
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include <glm/gtc/type_ptr.hpp>

namespace Draw {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        uniform mat4 view;
        uniform mat4 projection;

        uniform vec2 lineStart;
        uniform vec2 lineEnd;
        uniform vec4 inputLineColor;

        out vec4 lineColor;

        void main() {
            lineColor = inputLineColor;
            vec2 vertexPosition = mix(lineStart, lineEnd, gl_VertexID);
            vec4 worldSpacePosition = vec4(vertexPosition.x, vertexPosition.y, 0, 1);
            gl_Position = projection * view * worldSpacePosition;
        }
    )"""";

        constexpr const auto fragmentShader = R""""(
        #version 330 core
        in vec4 lineColor;
        out vec4 fragmentColor;

        void main() {
            fragmentColor = lineColor;
        }
    )"""";

        GLuint getVertexArrayObject() {
            GLuint vao;
            glGenVertexArrays(1, &vao); // glDeleteVertexArrays
            glBindVertexArray(vao);
            return vao;
        }

    }

    template<>
    void drawWireframe(OpenGL_GLFW_Context& context, Line data) {
        static const auto shader = Shader{"wireframe-shader", vertexShader, fragmentShader};
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto startLocation = glGetUniformLocation(shader, "lineStart");
        static const auto endLocation = glGetUniformLocation(shader, "lineEnd");
        static const auto colorLocation = glGetUniformLocation(shader, "inputLineColor");
        static const auto vao = getVertexArrayObject();

        //////////////////////////

        glBindVertexArray(vao);
        glUseProgram(shader);
        glLineWidth(data.lineWidth);
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform2fv(startLocation, 1, glm::value_ptr(data.startPosition));
        glUniform2fv(endLocation,   1, glm::value_ptr(data.endPosition));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glDrawArrays(GL_LINES, 0, 2);
    }
}