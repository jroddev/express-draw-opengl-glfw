cmake_minimum_required(VERSION 3.18)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)
project(
        express-draw-opengl-glfw
        VERSION 0.1.0
        LANGUAGES CXX
)

find_package(OpenGL REQUIRED)

FetchContent_Declare(
        express-draw
        GIT_REPOSITORY https://github.com/jroddev/express-draw
)
FetchContent_MakeAvailable(express-draw)


FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb)
FetchContent_MakeAvailable(stb)


add_library(express-draw-opengl-glfw
        src/OpenGL_GLFW_Context.cpp
        src/Frame.cpp src/DrawLine.cpp
        include/express-draw-opengl-glfw/shader/Shader.h
        src/shader/Shader.cpp
        src/shader/ShaderUtils.cpp
        include/express-draw-opengl-glfw/OpenGLWindow.h
        src/OpenGLWindow.cpp
        src/DrawQuad.cpp
        include/express-draw-opengl-glfw/mesh/TopLeftUnitQuad.h
        include/express-draw-opengl-glfw/mesh/CenteredUnitQuad.h
        include/express-draw-opengl-glfw/mesh/Vertex.h
        src/Camera.cpp
        src/DrawSprite.cpp
        src/Texture.cpp)
target_include_directories(express-draw-opengl-glfw
        PUBLIC
        ${express-draw_SOURCE_DIR}/include/
        ${glm_SOURCE_DIRECTORY}
        ${stb_SOURCE_DIR}
        include/)

target_link_libraries(express-draw-opengl-glfw OpenGL::GL)
target_link_libraries(express-draw-opengl-glfw glfw)
target_link_libraries(express-draw-opengl-glfw libglew_shared)