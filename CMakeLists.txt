cmake_minimum_required(VERSION 3.18)
project(
        express_draw
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)

configure_file(assets/textures/wooden_crate.png assets/textures/wooden_crate.png COPYONLY)
configure_file(assets/textures/green_bush.png assets/textures/green_bush.png COPYONLY)
configure_file(assets/fonts/DroidSans.ttf assets/fonts/DroidSans.ttf COPYONLY)
configure_file(assets/fonts/Arial.ttf assets/fonts/Arial.ttf COPYONLY)

add_subdirectory(express-draw-opengl-glfw)

add_executable(express_draw src/main.cpp)
target_include_directories(express_draw
        PRIVATE
        express-draw-opengl-glfw/include)
target_link_libraries(express_draw
        express-draw-opengl-glfw)