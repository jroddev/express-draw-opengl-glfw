
#ifndef EXPRESS_DRAW_SHADER_H
#define EXPRESS_DRAW_SHADER_H

#include <string_view>

struct Shader {
    Shader(std::string_view name, const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    // Clang-Tidy: 'operator unsigned int' must be marked explicit to avoid unintentional implicit conversions
    // NOLINTNEXTLINE
    operator unsigned int() const;

private:
    unsigned int shaderProgram;
};

#endif //EXPRESS_DRAW_SHADER_H
