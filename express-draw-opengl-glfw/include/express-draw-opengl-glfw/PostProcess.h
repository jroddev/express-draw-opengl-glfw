//#ifndef EXPRESS_DRAW_POSTPROCESS_H
//#define EXPRESS_DRAW_POSTPROCESS_H
//
//#include "include/express-draw/PostProcessing.h"
//#include "include/express-draw/PostProcessingTypes.h"
//#include "OpenGL_GLFW_Context.h"
//
///*
// Have 2 texture in process
// src, dst
// when post process take the dst and use it as the src then render into the new dst (prev src)
// to render to the screen set dst to 0 or whatever it need
// */
//
//
//namespace Draw {
//    template<>
//    void runPostProcess(OpenGL_GLFW_Context context, BlurPostProcess data) {
//        // switch context.renderDst and context.renderSrc
//        // render blur
//    }
//
//    template<>
//    void runPostProcess(OpenGL_GLFW_Context context, GrayScalePostProcess data) {
//        // switch context.renderDst and context.renderSrc
//        // render blur
//    }
//
//    template<>
//    void runPostProcess(OpenGL_GLFW_Context context, BloomPostProcess data) {
//        // switch context.renderDst and context.renderSrc
//        // render blur
//    }
//
//}
//
//#endif //EXPRESS_DRAW_POSTPROCESS_H
