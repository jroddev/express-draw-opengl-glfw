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

