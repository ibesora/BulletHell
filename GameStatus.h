#pragma once
#include "raylib.h"
#include "InputSequence.h"

class Screen;
class AssetStore;

class GameStatus {
public:
    GameStatus(Screen *initialScreen);
    void reset(Screen *initialScreen);
    Screen *getCurrentScreen();
    void update();
    void checkBarrelRollSequences();
    void updateClouds();
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
    InputSequence *getInputSequence();
    int getCloudsNumber();
    int getCloudYPosition(int index);
    void updateInputSequence();
    ~GameStatus();

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
    Screen *currentScreen;
    Vector2 currentPosition;
    InputSequence *inputSequence;
    std::vector<InputSequence::Input> barrelRollRightKeySequence;
    std::vector<InputSequence::Input> barrelRollLeftKeySequence;
    std::vector<CloudInfo> cloudPositions;
};