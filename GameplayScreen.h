#pragma once
#include "Screen.h"

class GameplayScreen : public Screen {
public:
    GameplayScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
private:
    int currentFrame;
    int currentRollFrame;
    int currentPitchFrame;
    Texture2D starshipRollTexture;
    Texture2D starshipPitchTexture;
    Rectangle currentFrameRec;
};