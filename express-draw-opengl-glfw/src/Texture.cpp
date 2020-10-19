
#include "express-draw-opengl-glfw/Texture.h"
#include <GL/glew.h>
#include <stdexcept>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string textureFileName) {
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w,h;
    const auto data = stbi_load(
            textureFileName.c_str(),
            &w,
            &h,
            &colorChannels,
            0);
    width = w;
    height = h;
    if (data) {
        std::cout << "Load Texture: " << textureFileName << " " << width << ", " << height << " has " << colorChannels << " channels\n";
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        stbi_image_free(data);
        throw std::runtime_error("Failed to load texture: " + textureFileName);
    }

}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, textureId);
}

Texture::Texture(OpenGLTexture openGlTexture, glm::ivec2 size, int colorChannels):
        textureId(openGlTexture),
        width(size.x),
        height(size.y),
        colorChannels(colorChannels){

}


