
#include <express-draw-opengl-glfw/shader/Shader.h>
#include <express-draw-opengl-glfw/shader/ShaderUtils.h>
#include <GL/glew.h>
#include <iostream>

Shader::Shader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc) {
    std::cout << "Compiling vertex shader for " << name << std::endl;
    auto vertexShader = ShaderUtils::compile(vertexSrc, ShaderUtils::SHADER_TYPE::VERT);
    std::cout << "Compiling fragment shader for " << name << std::endl;
    auto fragmentShader = ShaderUtils::compile(fragmentSrc, ShaderUtils::SHADER_TYPE::FRAG);
    std::cout << "linking shaders for " << name << std::endl;
    shaderProgram = ShaderUtils::link(vertexShader, fragmentShader);
    std::cout << "shader " << name << " loaded" << std::endl;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    std::cout << "destroy shader" << std::endl;
    glDeleteProgram(shaderProgram);
}

Shader::operator unsigned int() const {
    return shaderProgram;
}

