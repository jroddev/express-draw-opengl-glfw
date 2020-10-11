#include "express-draw/Frame.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"

namespace Draw {
    template<>
    void startFrame(OpenGL_GLFW_Context& context) {
        glfwPollEvents();
        glClearColor(0.3, 0.3, 0.35, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    template<>
    void endFrame(OpenGL_GLFW_Context& context) {
        glfwSwapBuffers(context.openglWindow->window);
    }
}
