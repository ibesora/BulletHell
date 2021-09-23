#pragma once
#include "GameStatus.h"
#include "Screen.h"

class LogoScreen : public Screen {
public:
    LogoScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
private:
    int currentFrame;
};