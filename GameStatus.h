#pragma once
#include "raylib.h"

class Screen;

class GameStatus {
public:
    GameStatus(Screen *initialScreen);
    Screen *getCurrentScreen();
    void update();
    void updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown);
    void setIsRightBarrelRolling(bool);
    void setIsLeftBarrelRolling(bool);
    void updatePosition(float x, float y);
    void changeCurrentScreen(Screen *nextScreen);
    Vector2 getCurrentPosition();
    Vector2 getCurrentScreenPosition();
    bool isPlayerGoingRight();
    bool isPlayerGoingLeft();
    bool isPlayerGoingUp();
    bool isPlayerGoingDown();
    bool isPlayerBarrelRolling();
    bool isPlayerBarrelRollingRight();
    bool isPlayerBarrelRollingLeft();
    ~GameStatus();

protected:
    bool isPlaying;
    bool isGoingRight;
    bool isGoingLeft;
    bool isGoingUp;
    bool isGoingDown;
    bool isRightBarrelRolling;
    bool isLeftBarrelRolling;
    Screen *currentScreen;
    Vector2 currentPosition;
};