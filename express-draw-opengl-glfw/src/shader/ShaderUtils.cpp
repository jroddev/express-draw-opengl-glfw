#include "express-draw-opengl-glfw/shader/ShaderUtils.h"
#include <stdexcept>
#include <unordered_map>
#include <GL/glew.h>

namespace ShaderUtils {

    using std::runtime_error;

    static auto shaderTypeToGLType = std::unordered_map<const SHADER_TYPE, unsigned int>{ // NOLINT(cert-err58-cpp)
            {SHADER_TYPE::VERT, GL_VERTEX_SHADER},
            {SHADER_TYPE::FRAG, GL_FRAGMENT_SHADER},
    };


    unsigned int  compile(const std::string& src, SHADER_TYPE shaderType) {
        const auto csrc =  src.c_str();
        auto shader = glCreateShader(shaderTypeToGLType[shaderType]);
        glShaderSource(shader, 1, &csrc, nullptr);
        glCompileShader(shader);

        int success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            throw runtime_error(string{"Shader::compile::failed: "} + infoLog);
        }
        return shader;
    }

    unsigned int link(unsigned int &vertexShader, unsigned int &fragmentShader) {
        auto shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, vertexShader);
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);

        int success;
        glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
            throw runtime_error(string{"Shader::link::failed: "} + infoLog);
        }

//        glValidateProgram(shaderProgram);
//        glGetShaderiv(shaderProgram, GL_VALIDATE_STATUS, &success);
//        if (!success) {
//            char infoLog[512];
//            glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//            throw runtime_error(string{"Shader::validate::failed: "} + infoLog);
//        }

        return shaderProgram;
    }

}