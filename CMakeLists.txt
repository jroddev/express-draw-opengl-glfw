cmake_minimum_required(VERSION 3.17)
project(
        express_draw-sample
        VERSION 0.1.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(assets/textures/wooden_crate.png assets/textures/wooden_crate.png COPYONLY)
configure_file(assets/textures/green_bush.png assets/textures/green_bush.png COPYONLY)
configure_file(assets/fonts/DroidSans.ttf assets/fonts/DroidSans.ttf COPYONLY)
configure_file(assets/fonts/Arial.ttf assets/fonts/Arial.ttf COPYONLY)

add_subdirectory(express-draw-opengl-glfw)

add_executable(express_draw-sample src/main.cpp)
target_include_directories(express_draw-sample
        PRIVATE
        express-draw-opengl-glfw/include)
target_link_libraries(express_draw-sample
        express-draw-opengl-glfw)