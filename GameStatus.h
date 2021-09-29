#pragma once
#include "raylib.h"
#include "InputSequence.h"

class Screen;
class AssetStore;

class GameStatus {
public:
    GameStatus(GameStatus &other) = delete;
    void operator=(const GameStatus &) = delete;
    static GameStatus &getInstance();
    void setInitialScreen(Screen *initialScreen);
    void reset();
    Screen *getCurrentScreen();
    void update();
    void updateInputs();
    void updateStarship();
    void updateBackground();
    void updateClouds();
    void updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown);
    void setIsRightBarrelRolling(bool);
    void setIsLeftBarrelRolling(bool);
    void updatePosition(float x, float y);
    void changeCurrentScreen(Screen *nextScreen);
    Vector2 getCurrentPosition();
    Vector2 getCurrentScreenPosition();
    Vector2 getBackgroundPosition();
    int getCurrentRollFrame();
    int getCurrentPitchFrame();
    bool isPlayerGoingRight();
    bool isPlayerGoingLeft();
    bool isPlayerGoingUp();
    bool isPlayerGoingDown();
    bool isPlayerBarrelRolling();
    bool isPlayerBarrelRollingRight();
    bool isPlayerBarrelRollingLeft();
    int getCloudsNumber();
    int getCloudYPosition(int index);
    ~GameStatus();

protected:
    GameStatus();

private:
    struct CloudInfo {
        int speed;
        int y;
        CloudInfo(int speed, int y) : speed(speed), y(y) {
        }
    };

    bool isPlaying;
    bool isGoingRight;
    bool isGoingLeft;
    bool isGoingUp;
    bool isGoingDown;
    bool isRightBarrelRolling;
    bool isLeftBarrelRolling;
    int currentRollFrame;
    int currentPitchFrame;
    Screen *currentScreen;
    Vector2 currentPosition;
    Vector2 backgroundPosition;
    std::vector<CloudInfo> cloudPositions;
};