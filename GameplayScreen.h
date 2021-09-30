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
    void drawPowerUps();
    void drawStarship();
    void drawForeground();
    void drawBullets();
    void drawEnemies();
    void drawEnemyBullets();
    void drawEnemyLife();
    void drawPlayerLife();
    void drawText();
    
    int textAnimFrame;
    Rectangle currentFrameRec;
    Rectangle currentBackgroundRect;
};