#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"

#include <filesystem>
#include <iostream>

Draw::OpenGL_GLFW_Context::OpenGL_GLFW_Context(const OpenGLWindow::Props& windowProps):
    openglWindow(std::make_unique<OpenGLWindow>(windowProps)){
}

bool Draw::OpenGL_GLFW_Context::isRunning() const {
    return !openglWindow->shouldClose();
}

void Draw::OpenGL_GLFW_Context::addDirectoryToFileHashes(const std::string_view path) {
    std::cout << "addDirectoryToFileHashes: " << path << std::endl;
    const auto hasher = std::hash<std::string_view>{};
    for (const auto& file : std::filesystem::recursive_directory_iterator{path}) {
        const auto& filepath = file.path();
        const auto hash = hasher(filepath.c_str());
        std::cout << filepath << ": " << hash << std::endl;
        fileHashes.emplace(hash, filepath);
    }
    std::cout << "----" << std::endl;
}

Texture Draw::OpenGL_GLFW_Context::getOrLoadTexture(const TextureIdentifier identifier) {
    const auto entry = textures.find(identifier);
    if (entry == textures.end()) {
        const auto fileHashEntry = fileHashes.find(static_cast<size_t>(identifier));
        if (fileHashEntry == fileHashes.end()) {
            throw std::runtime_error(
                    "Could not find filehash: " +
                    std::to_string(static_cast<size_t>(identifier)) +
                    ". Did you pre-cache this directory in context?");
        }
        const auto textureFilePath = fileHashEntry->second;
        const auto texture = Texture{textureFilePath};
        textures.emplace(identifier, texture);
        return texture;
    } else {
        return entry->second;
    }
}

Font::FontInfo Draw::OpenGL_GLFW_Context::getOrLoadFont(const std::string& fontPath, int size) {
    const auto fontIdentifier = fontPath + std::to_string(size);
    const auto entry = fonts.find(fontIdentifier);
    if (entry == fonts.end()) {
        const auto [fontInfo, fontTexture] = Font::loadFromFontFile("assets/fonts/Arial.ttf");
        fonts.emplace(
                fontIdentifier,
                fontInfo);
        textures.emplace(
                fontInfo.textureIdentifier,
                fontTexture);
        return fontInfo;
    } else {
        return entry->second;
    }
}

