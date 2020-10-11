#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "express-draw/Camera.h"
#include "express-draw/CameraTypes.h"
#include "express-draw-opengl-glfw/OpenGL_GLFW_Context.h"

namespace Draw {
    template<>
    void setCamera(OpenGL_GLFW_Context& context, const OrthographicSceneCamera& camera, const ViewportProperties& viewport) {
        static const constexpr glm::mat4 identityMatrix = glm::mat4{1.0f};

        const auto halfWidth = (viewport.size.x * camera.zoom)/2.f;
        const auto halfHeight = (viewport.size.y * camera.zoom)/2.f;
        const auto up = static_cast<float>(viewport.up);
        context.cameraProjectionMatrix = glm::ortho(
                -halfWidth,
                halfWidth,
                -up * halfHeight,
                up * halfHeight,
                -100.f,
                100.0f);

        const auto T = glm::translate(identityMatrix, {-camera.position.x , camera.position.y, 0.F});
        const auto R = glm::eulerAngleYXZ(0.F, 0.F, glm::radians(camera.rotation));
        context.cameraViewMatrix = T * R;
    }
}