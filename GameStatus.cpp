#include "GameStatus.h"
#include "Screen.h"
#include "raylib.h"

GameStatus::GameStatus(Screen* initialScreen) {
    this->isPlaying = false;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->isGoingUp = false;
    this->isGoingDown = false;
    this->isRightBarrelRolling = false;
    this->isLeftBarrelRolling = false;
    this->currentScreen = initialScreen;
    this->currentPosition = { 0.0f, 0.0f };
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        // TODO: Move all the logic of the player movement in Gameplay screen here?
    }

    this->getCurrentScreen()->updateGameStatus(this);
}

void GameStatus::updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown) {
    this->isGoingRight = goingRight;
    this->isGoingLeft = goingLeft;
    this->isGoingUp = goingUp;
    this->isGoingDown = goingDown;
}

void GameStatus::setIsRightBarrelRolling(bool rolling) { this->isRightBarrelRolling = rolling;  }
void GameStatus::setIsLeftBarrelRolling(bool rolling) { this->isLeftBarrelRolling = rolling;  }

void GameStatus::updatePosition(float x, float y) {
    this->currentPosition = { x, y };
}

void GameStatus::changeCurrentScreen(Screen *nextScreen) {
    // TODO: Do some kind of transition between screens?
    delete this->currentScreen;
    this->currentScreen = nextScreen;
    if (nextScreen->getType() == ScreenType::Gameplay) this->isPlaying = true;
    if (nextScreen->getType() == ScreenType::Ending) this->isPlaying = false;
}

Vector2 GameStatus::getCurrentPosition() {
    return this->currentPosition;
}

bool GameStatus::isPlayerGoingLeft() { return this->isGoingLeft; }
bool GameStatus::isPlayerGoingRight() { return this->isGoingRight; }
bool GameStatus::isPlayerGoingUp() { return this->isGoingUp; }
bool GameStatus::isPlayerGoingDown() { return this->isGoingDown; }
bool GameStatus::isPlayerBarrelRollingLeft() { return this->isLeftBarrelRolling; }
bool GameStatus::isPlayerBarrelRollingRight() { return this->isRightBarrelRolling; }

GameStatus::~GameStatus() {
    delete this->currentScreen;
}