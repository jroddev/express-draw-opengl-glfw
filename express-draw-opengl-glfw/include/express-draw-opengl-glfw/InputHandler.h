#ifndef EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H
#define EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H

class InputHandler {
public:
    virtual void receiveKeyboardInput(int key, int scancode, int action, int mods) = 0;
    virtual void receiveMouseButton(int button, int action, int mods) = 0;
    virtual void receiveMousePosition(double xPos, double yPos) = 0;
};

#endif //EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H
