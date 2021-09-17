#pragma once
#include "GameStatus.h"
#include "Screen.h"

class LogoScreen : public Screen {
public:
    LogoScreen();
    void updateGameStatus(GameStatus *current);
    void draw();
private:
    int currentFrame;
};