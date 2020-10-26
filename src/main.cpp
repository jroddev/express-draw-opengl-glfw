#include <iostream>

#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"
#include "express-draw/Frame.h"
#include "express-draw/Draw.h"
#include "express-draw/DrawTypes.h"
#include "express-draw/Camera.h"
#include "express-draw/CameraTypes.h"
#include "express-draw-opengl-glfw/TextRenderer.h"
#include <chrono>

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

    const auto uiCamera = Draw::OrthographicSceneCamera{
            .position = {300, -200},
            .zoom=1.F
    };

    const auto textToRender = convertToRenderableText(context, Draw::TextBlock{
        .transform{Draw::Transform2D::from(0,0,0,1,1)},
        .blockSize { 300.F, 100.F},
        .fontSize = 12,
        .font {"assets/fonts/Arial.ttf"},
        .text{"Hello there from the text renderer!"},
    });

    auto fps = RenderableText{.transform{}, .texture=Draw::TextureIdentifier{""}, .characters{}};
    auto lastFPSUpdate = std::chrono::high_resolution_clock::now();
    auto frameCounter = 0;

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
                .borderWidth=1.F,
                .pivotPoint=Draw::PIVOT_POINT::BOTTOM_RIGHT
        });

        Draw::draw(context, Draw::Sprite{
                .transform{ Draw::Transform2D::from(
                        0.F,0.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{1.F, 1.F, 1.F, 1.F},
                .textureRegion {0.F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/textures/wooden_crate.png"}},
                .pivotPoint = Draw::PIVOT_POINT::CENTER
        });


        Draw::draw(context, Draw::Sprite{
                .transform{ Draw::Transform2D::from(
                        0.F,0.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{1.F, 0.F, 1.F, 1.F},
                .textureRegion {0.5F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/textures/green_bush.png"}},
                .pivotPoint=Draw::PIVOT_POINT::BOTTOM_LEFT
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
        Draw::draw(context, textToRender);

        /////

        Draw::setCamera(context, uiCamera, {
                .size{context.openglWindow->width, context.openglWindow->height},
                .up = Draw::UP_AXIS::NEGATIVE_Y
        });

        Draw::draw(context, Draw::Sprite{
                .transform{ Draw::Transform2D::from(
                        0.F,0.F,
                        0.F,
                        30.F, 30.F
                )},
                .color{1.F, 1.F, 1.F, 1.F},
                .textureRegion {0.F, 0.F, 1.F, 1.F},
                .texture{Draw::TextureIdentifier{"assets/textures/wooden_crate.png"}},
                .pivotPoint = Draw::PIVOT_POINT::TOP_LEFT
        });



        Draw::draw(context, fps);


        Draw::drawWireframe(context, Draw::Quad{
                .transform = Draw::Transform2D::multi(
                        fps.transform,
                        Draw::Transform2D::from(
                                0,0,
                                0,
                                100.F,
                                100.F)),
                .color = {0.F, 1.F, 0.F, 1.F},
                .borderWidth = 0.2F,
                .pivotPoint = Draw::PIVOT_POINT::TOP_LEFT
        });

        Draw::drawWireframe(context, Draw::Quad{
                .transform = Draw::Transform2D::multi(
                        fps.transform,
                        Draw::Transform2D::from(
                                fps.boundingBox.x,
                                fps.boundingBox.y,
                                0,
                                fps.boundingBox.width,
                                fps.boundingBox.height)),
                .color = {1.F, 0.F, 0.F, 1.F},
                .borderWidth = 0.2F,
                .pivotPoint = Draw::PIVOT_POINT::TOP_LEFT
        });


        Draw::endFrame(context);

        frameCounter++;
        auto now = std::chrono::high_resolution_clock::now();
        auto fpsMillis = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFPSUpdate).count();
        if (fpsMillis > 1000) {
            fps = convertToRenderableText(context, Draw::TextBlock{
                    .transform{Draw::Transform2D::from(50,20,30,1,1)},
                    .blockSize { 100.F, 100.F},
                    .fontSize = 12,
                    .font {"assets/fonts/Arial.ttf"},
                    .text{std::to_string(frameCounter) + " FPS"},
            });
            frameCounter = 0;
            lastFPSUpdate = now;
        }
    }

    return 0;
}
