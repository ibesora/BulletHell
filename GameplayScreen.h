#pragma once
#include "Screen.h"

class GameplayScreen : public Screen {
public:
    GameplayScreen();
    void updateGameStatus(GameStatus *current);
    void draw();
};