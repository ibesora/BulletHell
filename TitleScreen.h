#pragma once
#include "Screen.h"

class TitleScreen : public Screen {
public:
    TitleScreen(int width, int height, const bool shouldAnimate = true);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
private:
    enum class Option : int { StartGame = 0, Credits, End };
    int currentFrame;
    Option currentSelectedOption;
};