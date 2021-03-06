#include <express-draw-opengl-glfw/shader/Shader.h>
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include <glm/gtc/type_ptr.hpp>
#include <express-draw-opengl-glfw/mesh/UnitQuad.h>


namespace Draw {

    namespace {

        constexpr const auto vertexShader = R""""(
        #version 330 core
        layout (location = 0) in vec2 aPos;

        uniform mat4 model;
        uniform mat4 view;
        uniform mat4 projection;
        uniform vec4 color;

        out vec4 outputColor;

        void main() {
            outputColor = color;
            gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
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

    }

    template<>
    void draw(OpenGL_GLFW_Context& context, const Quad& data) {
        static const auto shader = Shader{"quad-shader", vertexShader, fragmentShader};
        static const auto modelMatrixLocation = glGetUniformLocation(shader, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto colorLocation = glGetUniformLocation(shader, "color");

        const auto mesh = context.quadMeshes.at(data.pivotPoint);

        //////////////////////////

        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glUseProgram(shader);
        glLineWidth(data.borderWidth);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(data.transform.getGetLocalSpaceMatrix()));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, nullptr);
    }

    template<>
    void drawWireframe(OpenGL_GLFW_Context& context, const Quad& data) {
        static const auto shader = Shader{"quad-wireframe-shader", vertexShader, fragmentShader};
        static const auto modelMatrixLocation = glGetUniformLocation(shader, "model");
        static const auto viewMatrixLocation = glGetUniformLocation(shader, "view");
        static const auto projectionMatrixLocation = glGetUniformLocation(shader, "projection");
        static const auto colorLocation = glGetUniformLocation(shader, "color");

        const auto mesh = context.quadMeshes.at(data.pivotPoint);

        //////////////////////////

        glBindVertexArray(mesh.vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
        glUseProgram(shader);
        glLineWidth(data.borderWidth);
        glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(data.transform.getGetLocalSpaceMatrix()));
        glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraViewMatrix));
        glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(context.cameraProjectionMatrix));
        glUniform4fv(colorLocation, 1, glm::value_ptr(data.color));
        glDrawArrays(GL_LINE_LOOP, 0, 4);
    }

}