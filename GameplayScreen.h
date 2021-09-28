#pragma once
#include "Screen.h"

class AssetStore;

class GameplayScreen : public Screen {
public:
    GameplayScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);

private:
    void drawBackground();
    void drawStarship(GameStatus *status);
    void drawForeground(GameStatus *status);
    
    int currentRollFrame;
    int currentPitchFrame;
    Rectangle currentFrameRec;
    Rectangle currentBackgroundRect;
};