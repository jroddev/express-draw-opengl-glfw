
#include <express-draw-opengl-glfw/OpenGLWindow.h>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void debugMessageCallback(
        GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam) {
    switch (severity) {
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            std::cout << "OPENGL:NOTIF: " << message << std::endl;
            break;
        case GL_DEBUG_SEVERITY_LOW:
            std::cout << "OPENGL:INFO: " << message << std::endl;
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            std::cerr << "OPENGL:WARNING: " << message << std::endl;
            break;
        case GL_DEBUG_SEVERITY_HIGH:
            std::cerr << "OPENGL:ERROR: " << message << std::endl;
            break;
        default:
            std::cerr
                    << "OPENGL:UNKNOWN:severity:"
                    << std::hex
                    << severity
                    << std::dec
                    << ", message: "
                    << message
                    << std::endl;
    }
}

OpenGLWindow::OpenGLWindow(const Props &props) {
    if (!glfwInit()) {
        throw std::runtime_error("GLFW Initialization failed");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback([](int error, const char *description) {
        std::cerr << "GLFW Error [" << error << "]: " << description << std::endl;
    });

    width = props.size.x;
    height = props.size.y;
    window = glfwCreateWindow(
            width,
            height,
            props.title.begin(),
            nullptr,
            nullptr
    );
    assert(window != nullptr);
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, static_cast<void *>(this));
//    glfwSetKeyCallback(window, key_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//    glfwSetMouseButtonCallback(window, mouse_callback);


    const auto sizeChanged = [](GLFWwindow *_window, int _width, int _height) {
        glViewport(0, 0, _width, _height);
        auto self = static_cast<OpenGLWindow *>(glfwGetWindowUserPointer(_window));
        self->width = _width;
        self->height = _height;
    };
    glfwSetFramebufferSizeCallback(window, sizeChanged);

    if (auto glewInitResult = glewInit() != GLEW_OK) {
        const std::string errorString = reinterpret_cast<const char *>(
                glewGetErrorString(glewInitResult));
        throw std::runtime_error("GLFW GLEW Initialization failed: " + errorString);
    }

    if (!GLEW_VERSION_4_1) {
        throw std::runtime_error("GLEW_VERSION_4_1 not available");
    }

#ifndef __APPLE__
    glDebugMessageCallback(debugMessageCallback, nullptr);
#endif

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_ALWAYS);
}

OpenGLWindow::~OpenGLWindow() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool OpenGLWindow::shouldClose() const {
    return glfwWindowShouldClose(window);
}

