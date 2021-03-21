#ifndef EXPRESS_DRAW_OPENGL_GLFW_TEXTURE_H
#define EXPRESS_DRAW_OPENGL_GLFW_TEXTURE_H

#include <string>
#include <glm/glm.hpp>

using OpenGLTexture = unsigned int;

class Texture {
public:
    Texture(std::string textureFileName);
    Texture(OpenGLTexture openGlTexture, glm::ivec2 size, int colorChannels);

    unsigned int width, height;
    int colorChannels;
    unsigned int textureId; // opengl resource id
    void bind() const;
};

#endif
