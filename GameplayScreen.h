#pragma once
#include "Screen.h"

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
    
    Rectangle currentFrameRec;
    Rectangle currentBackgroundRect;
};