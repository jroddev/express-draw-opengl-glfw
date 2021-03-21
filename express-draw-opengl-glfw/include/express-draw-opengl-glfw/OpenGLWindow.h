
#ifndef EXPRESS_DRAW_OPENGL_GLFW__OPENGLWINDOW_H
#define EXPRESS_DRAW_OPENGL_GLFW__OPENGLWINDOW_H


#include <glm/glm.hpp>
#include <string>

struct GLFWwindow;

class OpenGLWindow {
public:
    struct Props {
        std::string_view title;
        glm::vec2 size;
    };

    explicit OpenGLWindow(const Props& props);
    ~OpenGLWindow();
    [[nodiscard]] bool shouldClose() const;

    GLFWwindow* window;
    int width, height;

};

#endif
