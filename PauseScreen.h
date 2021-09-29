#pragma once
#include "Screen.h"

class PauseScreen : public Screen {
public:
    PauseScreen(int width, int height);
    void updateGameStatus();
    void draw();
private:
    enum class Option : int { Continue = 0, BackToTitleScreen, End };
    Option currentSelectedOption;
};