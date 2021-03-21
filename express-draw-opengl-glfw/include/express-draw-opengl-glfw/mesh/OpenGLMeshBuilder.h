
#ifndef EXPRESS_DRAW_SAMPLE_OPENGLMESHBUILDER_H
#define EXPRESS_DRAW_SAMPLE_OPENGLMESHBUILDER_H

#include "OpenGLMeshProperties.h"
#include "Vertex.h"

template<size_t VertexCount, size_t IndexCount>
OpenGLMeshProperties uploadMeshToOpenGL(
        const std::array<Vertex, VertexCount>& vertices,
        const std::array<int, IndexCount>& indices,
        int stride,
        int textureCoordIndexOffset) {
    GLuint vao;
    glGenVertexArrays(1, &vao); // glDeleteVertexArrays
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(
            GL_ARRAY_BUFFER,
            sizeof(vertices),
            vertices.data(),
            GL_STATIC_DRAW);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(
            GL_ELEMENT_ARRAY_BUFFER,
            sizeof(indices),
            indices.data(),
            GL_STATIC_DRAW);

    glVertexAttribPointer(
            0,
            2,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*) nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
            1,
            2,
            GL_FLOAT, GL_FALSE,
            stride,
            (void*)(textureCoordIndexOffset * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    return {
            .vao = vao,
            .vbo = vbo,
            .ebo = ebo,
            .indicesSize = static_cast<int>(indices.size())
    };
}

#endif //EXPRESS_DRAW_SAMPLE_OPENGLMESHBUILDER_H
