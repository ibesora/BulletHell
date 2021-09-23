#pragma once
#include "Screen.h"

class EndingScreen : public Screen {
public:
    EndingScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
private:
    enum class Option : int { NextRun = 0, BackToTitle, End };
    int currentFrame;
    Option currentSelectedOption;
};