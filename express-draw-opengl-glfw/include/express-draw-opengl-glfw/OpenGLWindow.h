
#ifndef EXPRESS_DRAW_OPENGLWINDOW_H
#define EXPRESS_DRAW_OPENGLWINDOW_H


#include <glm/glm.hpp>
#include <string>

class GLFWwindow;

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

#endif //EXPRESS_DRAW_OPENGLWINDOW_H
