#pragma once
#include "InputSequence.h"
#include "raylib.h"

class InputHandler {
public:
    InputHandler(InputHandler &other) = delete;
    void operator=(const InputHandler &) = delete;
    ~InputHandler();
    static InputHandler &getInstance();
    void update();
    void reset();
    bool isKeyDown(KeyboardKey key);
    bool isKeyUp(KeyboardKey key);
    bool isKeyPressed(KeyboardKey key);
    bool isKeyReleased(KeyboardKey key);
    bool checkRightBarrelRoll();
    bool checkLeftBarrelRoll();
protected:
    InputHandler();
private:
    InputSequence *inputSequence;
    std::vector<InputSequence::Input> barrelRollRightKeySequence;
    std::vector<InputSequence::Input> barrelRollLeftKeySequence;
};
