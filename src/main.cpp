#include <iostream>

#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include "express-draw/Frame.h"
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw/Camera.h"
#include "express-draw/CameraTypes.h"
#include "express-draw/TextureIdentifier.h"
#include "express-draw-opengl-glfw/font/FontLoader.h"

int main() {
    std::cout << "Hello, World!!" << std::endl;


    auto context = Draw::OpenGL_GLFW_Context{
        OpenGLWindow::Props{
            .title{"window"},
            .size{600, 400}
        }
    };

    context.addDirectoryToFileHashes("assets/");
    const auto arialFont = Font::loadFromFontFile("assets/fonts/Arial.ttf", "Arial");
    context.textures.emplace(
            std::get<0>(arialFont).textureIdentifier,
            std::get<1>(arialFont));

//    const auto droidFont = Font::loadFromFontFile("assets/fonts/DroidSans.ttf", "Droid");
//    context.textures.emplace(
//            std::get<0>(droidFont).textureIdentifier,
//            std::get<1>(droidFont));

    const auto camera = Draw::OrthographicSceneCamera{
            .zoom=1.F
    };

    while(context.isRunning()) {
        Draw::startFrame(context);
        Draw::setCamera(context, camera, {
            .size{context.openglWindow->width, context.openglWindow->height},
            .up = Draw::UP_AXIS::NEGATIVE_Y
        });

        Draw::draw(context, Draw::Quad{
                .position{0.F,0.F},
                .size{30.F, 30.F},
                .rotation = 0.F,
                .color{0.F, 0.F, 1.F, 1.F},
                .borderWidth=1.F
        });

        Draw::drawWireframe(context, Draw::Quad{
                .position{5.F,5.F},
                .size{30.F, 30.F},
                .rotation = 0.F,
                .color{0.F, 1.F, 1.F, 1.F},
                .borderWidth=1.F
        });

        Draw::draw(context, Draw::Sprite{
                .texture{TextureIdentifier{"assets/textures/wooden_crate.png"}},
                .position{0.F,-50.F},
                .size{30.F, 30.F},
                .rotation = 0.F,
                .color{1.F, 1.F, 1.F, 1.F}
        });

        Draw::draw(context, Draw::Sprite{
                .texture{TextureIdentifier{"assets/textures/green_bush.png"}},
                .position{50.F,-50.F},
                .size{30.F, 30.F},
                .rotation = 0.F,
                .color{1.F, 1.F, 1.F, 1.F}
        });


        Draw::drawWireframe(context, Draw::Line{
                .startPosition{0.F, 0.F},
                .endPosition{100.F, 0.F},
                .color{1.F, 0.F, 0.F, 1.F},
        });

        Draw::drawWireframe(context, Draw::Line{
                .startPosition{0.F, 0.F},
                .endPosition{0.F, 100.F},
                .color{0.F, 1.F, 0.F, 1.F},
        });


        Draw::draw(context, Draw::Sprite{
                .texture{TextureIdentifier{"assets/fonts/Arial.ttf"}},
                .position{-1000.F,-100.F},
                .size{2867.F, 45.F},
                .rotation = 0.F,
                .color{1.F, 1.F, 1.F, 1.F}
        });



        Draw::endFrame(context);

    }

    return 0;
}
