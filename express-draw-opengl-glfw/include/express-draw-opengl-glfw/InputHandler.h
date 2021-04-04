#ifndef EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H
#define EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H

class InputHandler {
public:
    virtual void receiveInput(int key, int scancode, int action, int mods) = 0;
};

#endif //EXPRESS_DRAW_SAMPLE_INPUTHANDLER_H
