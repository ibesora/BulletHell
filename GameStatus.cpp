#include "GameStatus.h"
#include "Screen.h"
#include "EndingScreen.h"
#include "raylib.h"
#include "AssetStore.h"
#include "InputHandler.h"
#include "Player.h"
#include "Enemy.h";
#include "PowerUp.h"

const int BackgroundSpeed = 5;
const int BackgroundWidthInPx = 1920;
const int CloudsMinSpeed = 5;
const int CloudsMaxSpeed = 10;
const float CloudProbability = 0.015f;
const float PowerUpProbability = 0.005;
const int StarshipWidthInPx = 256;
const int StarshipHeightInPx = 256;

GameStatus::GameStatus() {
    this->isPlaying = false;
    this->enemy = nullptr;
    this->player = nullptr;
    this->currentScreen = nullptr;
    this->backgroundPosition = { 0.0f, 0.0f };
}

GameStatus &GameStatus::getInstance() {
    static GameStatus instance;
    return instance;
}

Player* GameStatus::getPlayer() {
    return this->player;
}

void GameStatus::setInitialScreen(Screen* initialScreen) {
    this->currentScreen = initialScreen;
    this->reset();
}

void GameStatus::reset() {
    delete this->player;
    delete this->enemy;

    this->isPlaying = this->currentScreen->getType() == ScreenType::Gameplay;
    this->player = new Player((float)this->currentScreen->getWidth() / 2 - StarshipWidthInPx / 2, (float)this->currentScreen->getHeight() - StarshipHeightInPx);
    this->enemy = new Enemy(this->currentScreen->getWidth() - (float)AssetStore::getInstance().getMainEnemyTexture().width / 2, -50.0f);
    this->backgroundPosition = { 0.0f, 0.0f };
    this->cloudPositions.clear();
    this->powerUps.clear();
    InputHandler::getInstance().reset();
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        this->updateInputs();
        this->updateStarship();
        this->updateEnemies();
        this->updateBackground();
        this->updateClouds();
        this->updatePowerUps();
        if (this->player->isBeingHit()) this->changeCurrentScreen(new EndingScreen(this->currentScreen->getWidth(), this->currentScreen->getHeight()));
    }

    this->getCurrentScreen()->updateGameStatus();
}

void GameStatus::updateInputs() {
    InputHandler::getInstance().update();
    if (InputHandler::getInstance().checkRightBarrelRoll()) this->player->setIsRightBarrelRolling(true);
    else if (InputHandler::getInstance().checkLeftBarrelRoll()) this->player->setIsLeftBarrelRolling(true);
}

void GameStatus::updateStarship() {
    this->player->update(this->enemy);
}

void GameStatus::updateEnemies() {
    this->enemy->update(this->player);
}

void GameStatus::updateBackground() {
    // The background is bigger than the game window so we need to compute which part of
    // the background we need to draw. Basically the background is constantly scrolling
    // down and is moved right/left depending on the player position
    const int starshipSpriteCenter = (int)this->player->getPosition().x + StarshipWidthInPx / 2;
    const int halfWidth = this->currentScreen->getWidth() / 2;
    if (starshipSpriteCenter <= halfWidth) {
        this->backgroundPosition.x = 0.0f;
    }
    else if (starshipSpriteCenter > halfWidth && starshipSpriteCenter < BackgroundWidthInPx - halfWidth) {
        this->backgroundPosition.x = (float)(starshipSpriteCenter - halfWidth);
    }
    else {
        this->backgroundPosition.x = (float)(BackgroundWidthInPx - this->currentScreen->getWidth());
    }

    this->backgroundPosition.y -= (float)BackgroundSpeed;
}

void GameStatus::updateClouds() {
    // Check if we add another cloud layer
    const float diceThrow = (float)std::rand() / (float)RAND_MAX;
    const bool shouldWeAddACloud = diceThrow < CloudProbability;
    if (shouldWeAddACloud) {
        const int speed = (float)(std::rand() % (CloudsMaxSpeed - CloudsMinSpeed) + CloudsMinSpeed);
        CloudInfo info = CloudInfo(speed, -AssetStore::getInstance().getForegroundTexture().height);
        this->cloudPositions.push_back(info);
    }

    // Clouds position update
    for (int i = 0; i < this->cloudPositions.size(); ++i) {
        this->cloudPositions[i].y += this->cloudPositions[i].speed;
    }
}

void GameStatus::updatePowerUps() {
    const float diceThrow = (float)std::rand() / (float)RAND_MAX;
    const bool shouldWeAddAPowerUp = diceThrow < PowerUpProbability;
    if (shouldWeAddAPowerUp) {
        const float posX = (float)(std::rand() % (BackgroundWidthInPx - AssetStore::getInstance().getPowerUpTexture().width));
        this->powerUps.push_back(PowerUp(posX, -AssetStore::getInstance().getPowerUpTexture().height));
    }

    // PowerUps position update
    std::vector<PowerUp> aux;
    for (int i = 0; i < this->powerUps.size(); ++i) {
        this->powerUps[i].update();
        if (!this->player->checkCollision(this->powerUps[i].getPosition())) {
            aux.push_back(this->powerUps[i]);
        }
        else {
            this->player->setPowerLevel(this->player->getPowerLevel() + 1);
        }
    }
    this->powerUps = aux;
}

void GameStatus::changeCurrentScreen(Screen *nextScreen) {
    // TODO: Do some kind of transition between screens?
    delete this->currentScreen;
    this->currentScreen = nextScreen;
    this->isPlaying = (this->currentScreen->getType() == ScreenType::Gameplay);
}

Vector2 GameStatus::getEnemyPosition() {
    return this->enemy->getPosition();
}

Vector2 GameStatus::getPlayerScreenPosition() {
    // If X position is less than half the screen width, we set that as X position
    // If it's in between half the screen width and BacgroundWidthInPx - halfWidth we set the X as the center screen
    // If X position is more than BacgroundWidthInPx - halfWidth we set that as the X position
    const int halfWidth = this->getCurrentScreen()->getWidth() / 2;
    const Vector2 currentPosition = this->player->getPosition();
    const int starshipSpriteCenter = currentPosition.x + StarshipWidthInPx / 2;
    int screenPositionX = currentPosition.x;
    const int screenPositionY = currentPosition.y;

    if (starshipSpriteCenter <= halfWidth) {}
    else if (starshipSpriteCenter > halfWidth && starshipSpriteCenter < BackgroundWidthInPx - halfWidth) { screenPositionX = halfWidth - StarshipWidthInPx / 2; }
    else { screenPositionX = halfWidth + currentPosition.x - (BackgroundWidthInPx - halfWidth); }

    return { (float)screenPositionX, (float)screenPositionY };
}

Vector2 GameStatus::getBackgroundPosition() { return this->backgroundPosition; }
int GameStatus::getCloudsNumber() { return this->cloudPositions.size(); }
int GameStatus::getCloudYPosition(int index) { return this->cloudPositions[index].y; }

int GameStatus::getBulletsNumber() { return this->player->getBulletPositions().size(); }
GameStatus::BulletInfo GameStatus::getBullet(int index) { return this->player->getBulletPositions()[index]; }
int GameStatus::getEnemyBulletsNumber() { return this->enemy->getBulletPositions().size(); }
GameStatus::BulletInfo GameStatus::getEnemyBullet(int index) { return this->enemy->getBulletPositions()[index]; }
int GameStatus::getPowerUpsNumber() { return this->powerUps.size(); }
PowerUp GameStatus::getPowerUp(int index) { return this->powerUps[index]; }
bool GameStatus::isPlayerBeingHit() { return this->player->isBeingHit(); }
bool GameStatus::isEnemyBeingHit() { return this->enemy->isBeingHit(); }

GameStatus::~GameStatus() {
    delete this->currentScreen;
    delete this->enemy;
}