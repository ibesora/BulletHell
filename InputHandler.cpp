#include "InputHandler.h"
#include "raylib.h"

const int RollTimeInMilliseconds = 150;

InputHandler::InputHandler() {

    this->inputSequence = new InputSequence(3);

    //Define special input sequences
    //Barrel rolls
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Released));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Released));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
}

InputHandler &InputHandler::getInstance() {
    static InputHandler instance;
    return instance;
}

void InputHandler::update() {
    // Handle button presses and releases and add it to the input sequence queue
    if (this->isKeyDown(KEY_LEFT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_LEFT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_LEFT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_LEFT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_LEFT);
        }
    }

    if (this->isKeyDown(KEY_RIGHT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_RIGHT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_RIGHT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_RIGHT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_RIGHT);
        }
    }
}

void InputHandler::reset() {
    this->inputSequence->clear();
}

bool InputHandler::checkRightBarrelRoll() {
    return this->inputSequence->checkSequence(this->barrelRollRightKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds));
}

bool InputHandler::checkLeftBarrelRoll() {
    return this->inputSequence->checkSequence(this->barrelRollLeftKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds));
}

bool InputHandler::isKeyDown(KeyboardKey key) { return IsKeyDown(key); }
bool InputHandler::isKeyUp(KeyboardKey key) { return IsKeyUp(key); }
bool InputHandler::isKeyPressed(KeyboardKey key) { 
    return IsKeyPressed(key);
}
bool InputHandler::isKeyReleased(KeyboardKey key) { return IsKeyReleased(key); }

InputHandler::~InputHandler() {
    delete this->inputSequence;
}
