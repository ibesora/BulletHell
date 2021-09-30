#pragma once
#include "raylib.h"
#include "InputSequence.h"

class Screen;
class AssetStore;
class Enemy;
class Player;
class PowerUp;

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
    Player* getPlayer();
    Vector2 getEnemyPosition();
    Vector2 getPlayerScreenPosition();
    Vector2 getBackgroundPosition();
    int getCloudsNumber();
    int getCloudYPosition(int index);
    int getBulletsNumber();
    BulletInfo getBullet(int index);
    int getEnemyBulletsNumber();
    BulletInfo getEnemyBullet(int index);
    int getPowerUpsNumber();
    PowerUp getPowerUp(int index);
    bool isPlayerBeingHit();
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
    void updatePowerUps();

private:
    struct CloudInfo {
        int speed;
        int y;
        CloudInfo(int speed, int y) : speed(speed), y(y) {}
    };

    bool isPlaying;
    Screen *currentScreen;
    Vector2 backgroundPosition;
    std::vector<CloudInfo> cloudPositions;
    std::vector<PowerUp> powerUps;
    Enemy *enemy;
    Player *player;
};