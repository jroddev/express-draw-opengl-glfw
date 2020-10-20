#include <iostream>

#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include "express-draw/Frame.h"
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw/Camera.h"
#include "express-draw/CameraTypes.h"
#include "express-draw-opengl-glfw/TextRenderer.h"


int main() {
    std::cout << "Hello, World!!" << std::endl;

    auto context = Draw::OpenGL_GLFW_Context{
        OpenGLWindow::Props{
            .title{"window"},
            .size{600, 400}
        }
    };

    context.addDirectoryToFileHashes("assets/");

    const auto camera = Draw::OrthographicSceneCamera{
            .zoom=1.F
    };

    const auto textToRender = convertToRenderableText(context, Draw::TextBlock{
        .transform{Draw::Transform2D::from(0,0,45,1,1)},
        .blockSize { 300.F, 100.F},
        .fontSize = 48,
        .font {"assets/fonts/Arial.ttf"},
        .text{"[Hello there from the text renderer!]"},

    });

    while(context.isRunning()) {
        Draw::startFrame(context);
        Draw::setCamera(context, camera, {
            .size{context.openglWindow->width, context.openglWindow->height},
            .up = Draw::UP_AXIS::NEGATIVE_Y
        });

        Draw::draw(context, Draw::Quad{
                .transform{ Draw::Transform2D::from(
                        0.F,0.F,
                        0.F,
                        30.F, 30.F
                        )},
                .color{0.F, 0.F, 1.F, 1.F},
                .borderWidth=1.F
        });

        Draw::drawWireframe(context, Draw::Quad{
                .transform{ Draw::Transform2D::from(
                        5.F,5.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{0.F, 1.F, 1.F, 1.F},
                .borderWidth=1.F
        });

        Draw::draw(context, Draw::Sprite{
                .transform{ Draw::Transform2D::from(
                        0.F,-50.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{1.F, 1.F, 1.F, 1.F},
                .textureRegion {0.F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/textures/wooden_crate.png"}},
        });

        Draw::draw(context, Draw::Sprite{
                .transform{ Draw::Transform2D::from(
                        50.F,-50.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{1.F, 0.F, 1.F, 1.F},
                .textureRegion {0.5F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/textures/green_bush.png"}},
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
                .transform{ Draw::Transform2D::from(
                        -1000.F,-100.F,
                        0.F,
                        2867.F, 45.F
                )},
                .color{1.F, 1.F, 1.F, 1.F},
                .textureRegion {0.F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/fonts/Arial.ttf48"}}
        });

        Draw::draw(context, textToRender);
        Draw::drawWireframe(context, Draw::Quad{
                .transform{ Draw::Transform2D::from(
                        0.F,0.F,
                        0.F,
                        300.F, 100.F
                )},
                .color{0.F, 1.F, 1.F, 0.2F},
                .borderWidth=1.F
        });


        Draw::endFrame(context);

    }

    return 0;
}
