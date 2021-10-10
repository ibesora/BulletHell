#pragma once
#include "Screen.h"

class WinScreen : public Screen {
public:
    WinScreen(int width, int height);
    void updateGameStatus();
    void draw();
private:
    int currentFrame;
};