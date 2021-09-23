#pragma once
#include "raylib.h"

class Screen;

class GameStatus {
public:
    GameStatus(Screen *initialScreen);
    Screen *getCurrentScreen();
    void update();
    void updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown);
    void updatePosition(float x, float y);
    void changeCurrentScreen(Screen *nextScreen);
    Vector2 getCurrentPosition();
    bool wasPlayerGoingRight();
    bool wasPlayerGoingLeft();
    ~GameStatus();

protected:
    bool isPlaying;
    bool wasGoingRight;
    bool wasGoingLeft;
    Screen *currentScreen;
    Vector2 currentPosition;
};