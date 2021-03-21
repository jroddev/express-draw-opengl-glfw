cmake_minimum_required(VERSION 3.17)
include(FetchContent)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG 3.3.2)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake
        GIT_TAG glew-cmake-2.1.0)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm
        GIT_TAG 0.9.9.8)
FetchContent_MakeAvailable(glm)

FetchContent_Declare(
        stb
        GIT_REPOSITORY https://github.com/nothings/stb)
FetchContent_MakeAvailable(stb)

find_package(Freetype REQUIRED)
if(FREETYPE_FOUND)
    set(FREETYPE_INCLUDE_DIRS "${FREETYPE_INCLUDE_DIRS}" PARENT_SCOPE)
    set(FREETYPE_LIBRARIES "${FREETYPE_LIBRARIES}" PARENT_SCOPE)
endif()


FetchContent_Declare(
        ranges-v3
        GIT_REPOSITORY https://github.com/ericniebler/range-v3
        GIT_TAG 0.10.0)
FetchContent_MakeAvailable(ranges-v3)


add_library(express-draw-opengl-glfw
        src/OpenGL_GLFW_Context.cpp
        src/Frame.cpp src/DrawLine.cpp
        include/express-draw-opengl-glfw/shader/Shader.h
        src/shader/Shader.cpp
        src/shader/ShaderUtils.cpp
        include/express-draw-opengl-glfw/OpenGLWindow.h
        src/OpenGLWindow.cpp
        src/DrawQuad.cpp
        include/express-draw-opengl-glfw/mesh/UnitQuad.h
        include/express-draw-opengl-glfw/mesh/Vertex.h
        src/Camera.cpp
        src/DrawSprite.cpp
        src/Texture.cpp
        src/DrawText.cpp
        src/font/FontLoader.cpp include/express-draw-opengl-glfw/TextRenderer.h src/TextRenderer.cpp include/express-draw-opengl-glfw/mesh/OpenGLMeshProperties.h include/express-draw-opengl-glfw/mesh/OpenGLMeshBuilder.h)
target_include_directories(express-draw-opengl-glfw
        PUBLIC
        ${express-draw_SOURCE_DIR}/include/
        ${glm_SOURCE_DIR}
        ${stb_SOURCE_DIR}
        ${ranges-v3_SOURCE_DIR}/include/
        ${FREETYPE_INCLUDE_DIRS}
        include/)

target_link_libraries(express-draw-opengl-glfw OpenGL::GL)
target_link_libraries(express-draw-opengl-glfw glfw)
target_link_libraries(express-draw-opengl-glfw libglew_shared)
target_link_libraries(express-draw-opengl-glfw ${FREETYPE_LIBRARIES})

set(BUILD_FLAGS "${BUILD_FLAGS} -std=c++20 -Wall -Wextra -pedantic")
# Warnings as Errors
#set(BUILD_FLAGS "${BUILD_FLAGS} -Werror")
set_target_properties(express-draw-opengl-glfw PROPERTIES COMPILE_FLAGS ${BUILD_FLAGS})
