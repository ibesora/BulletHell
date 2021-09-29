#pragma once
#include "Screen.h"
#include "GameStatus.h";
#include <vector>

class AssetStore;

class GameplayScreen : public Screen {
public:
    GameplayScreen(int width, int height);
    void updateGameStatus();
    void draw();

private:
    void updateStarshipTexture();
    void updateBackgroundTexture();
    void drawBackground();
    void drawStarship();
    void drawForeground();
    void drawBullets();
    void drawEnemies();
    void drawEnemyBullets();
    
    Rectangle currentFrameRec;
    Rectangle currentBackgroundRect;
};