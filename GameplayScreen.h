#pragma once
#include "Screen.h"
#include <stack>
#include "InputSequence.h"

class GameplayScreen : public Screen {
public:
    GameplayScreen(int width, int height);
    void updateGameStatus(GameStatus *current);
    void draw(GameStatus *current);
    ~GameplayScreen();
private:
    void updateInputSequence();

    int inputSequenceFrame;
    InputSequence *inputSequence;
    int currentRollFrame;
    int currentPitchFrame;
    Texture2D starshipRollTexture;
    Texture2D starshipPitchTexture;
    Rectangle currentFrameRec;
    std::vector<InputSequence::Input> barrelRollRightKeySequence;
    std::vector<InputSequence::Input> barrelRollLeftKeySequence;
};