#pragma once
#include "Screen.h"

class HowToPlayScreen : public Screen {
public:
    HowToPlayScreen(int width, int height);
    void updateGameStatus();
    void draw();
private:
    int currentFrame;
    Rectangle currentPitchUpAnimRec;
    Rectangle currentPitchDownAnimRec;
    Rectangle currentRollRightAnimRec;
    Rectangle currentRollLeftAnimRec;
    Rectangle currentBarrelRollLeftAnimRec;
    Rectangle currentBarrelRollRightAnimRec;
    Rectangle currentPowerUpAnimRec;
};