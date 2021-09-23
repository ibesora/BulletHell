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
    bool isPlayerGoingRight();
    bool isPlayerGoingLeft();
    bool isPlayerGoingUp();
    bool isPlayerGoingDown();
    ~GameStatus();

protected:
    bool isPlaying;
    bool isGoingRight;
    bool isGoingLeft;
    bool isGoingUp;
    bool isGoingDown;
    Screen *currentScreen;
    Vector2 currentPosition;
};