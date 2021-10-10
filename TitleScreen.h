#pragma once
#include "Screen.h"

class TitleScreen : public Screen {
public:
    TitleScreen(int width, int height, const bool shouldAnimate = true);
    void updateGameStatus();
    void draw();
private:
    enum class Option : int { StartGame = 0, HowToPlay, Credits, End };
    int currentFrame;
    Option currentSelectedOption;
};