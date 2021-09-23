#pragma once
#include "Screen.h"

class PauseScreen : public Screen {
public:
    PauseScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
private:
    enum class Option : int { Continue = 0, BackToTitleScreen, End };
    Option currentSelectedOption;
};