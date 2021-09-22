#pragma once
#include "Screen.h"

class PauseScreen : public Screen {
public:
    PauseScreen();
    void updateGameStatus(GameStatus *current);
    void draw();
private:
    enum class Option : int { Continue = 0, BackToTitleScreen, End };
    Option currentSelectedOption;
};