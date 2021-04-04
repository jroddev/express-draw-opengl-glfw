#ifndef EXPRESS_DRAW_OPENGL_GLFW_CONTEXT_H
#define EXPRESS_DRAW_OPENGL_GLFW_CONTEXT_H

#include "express-draw-opengl-glfw/Texture.h"
#include "express-draw/TextureIdentifier.h"

#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OpenGLWindow.h"

#include <unordered_map>
#include <express-draw-opengl-glfw/font/FontLoader.h>
#include <express-draw/DrawTypes.h>
#include <express-draw-opengl-glfw/mesh/OpenGLMeshProperties.h>
#include <express-draw-opengl-glfw/InputHandler.h>

namespace Draw {

    class OpenGL_GLFW_Context {
    public:
        explicit OpenGL_GLFW_Context(const OpenGLWindow::Props& windowProps);
        void addDirectoryToFileHashes(std::string_view path);
        [[nodiscard]] bool isRunning() const;
        void setInputHandler(InputHandler* handler);

        std::unique_ptr<OpenGLWindow> openglWindow;
        glm::mat4 cameraViewMatrix{};
        glm::mat4 cameraProjectionMatrix{};

        std::unordered_map<std::size_t, std::string> fileHashes;
        std::unordered_map<const TextureIdentifier, Texture, TextureIdentifierHasher, TextureIdentifierCompare> textures;
        std::unordered_map<std::string, Font::FontInfo> fonts;

        Texture getOrLoadTexture(TextureIdentifier identifier);
        Font::FontInfo getOrLoadFont(const std::string& fontPath, int size);

        std::unordered_map<PIVOT_POINT, OpenGLMeshProperties> quadMeshes;
        void loadQuadMeshes();

    private:
        InputHandler* inputHandler;
    };
}

#endif //EXPRESS_DRAW_OPENGL_GLFW_CONTEXT_H
