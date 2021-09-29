#pragma once
#include "raylib.h"
#include "InputSequence.h"

class Screen;
class AssetStore;
class Enemy;

class GameStatus {
public:
    struct BulletInfo {
        Vector2 speed;
        Vector2 position;
        BulletInfo(Vector2 speed, Vector2 position) : speed(speed), position(position) {}
    };

    GameStatus(GameStatus &other) = delete;
    void operator=(const GameStatus &) = delete;
    static GameStatus &getInstance();
    void setInitialScreen(Screen *initialScreen);
    void reset();
    Screen *getCurrentScreen();
    void update();
    void changeCurrentScreen(Screen *nextScreen);
    Vector2 getPlayerPosition();
    Vector2 getEnemyPosition();
    Vector2 getPlayerScreenPosition();
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
    int getBulletsNumber();
    BulletInfo getBullet(int index);
    int getEnemyBulletsNumber();
    BulletInfo getEnemyBullet(int index);
    bool isEnemyBeingHit();
    ~GameStatus();

protected:
    GameStatus();
    void updateInputs();
    void updateBullets();
    void updateStarship();
    void updateEnemies();
    void updateBackground();
    void updateClouds();
    void updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown);
    void setIsRightBarrelRolling(bool);
    void setIsLeftBarrelRolling(bool);
    void updatePosition(float x, float y);

private:
    struct CloudInfo {
        int speed;
        int y;
        CloudInfo(int speed, int y) : speed(speed), y(y) {}
    };

    void createBullet();

    bool isPlaying;
    bool isGoingRight;
    bool isGoingLeft;
    bool isGoingUp;
    bool isGoingDown;
    bool isRightBarrelRolling;
    bool isLeftBarrelRolling;
    int currentRollFrame;
    int currentPitchFrame;
    int currentBulletFrame;
    Screen *currentScreen;
    Vector2 currentPosition;
    Vector2 backgroundPosition;
    std::vector<CloudInfo> cloudPositions;
    std::vector<BulletInfo> bulletPositions;
    Enemy *enemy;
};