#ifndef EXPRESS_DRAW_OPENGL_GLFW__SHADERUTILS_H
#define EXPRESS_DRAW_OPENGL_GLFW__SHADERUTILS_H

#include <string>

namespace ShaderUtils {
    using std::string;
    enum class SHADER_TYPE {
        VERT,
        FRAG
    };

    unsigned int compile(const std::string& src, SHADER_TYPE shaderType);
    unsigned int  link(unsigned int &vertexShader, unsigned int &fragmentShader);
};


#endif //EXPRESS_DRAW_OPENGL_GLFW_SHADERUTILS_H
