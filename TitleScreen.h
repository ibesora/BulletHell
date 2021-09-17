#pragma once
#include "Screen.h"

enum class Option : int { StartGame = 0, Credits, End };

class TitleScreen : public Screen {
public:
    TitleScreen();
    void updateGameStatus(GameStatus *current);
    void draw();
private:
    int currentFrame;
    Option currentSelectedOption;
};