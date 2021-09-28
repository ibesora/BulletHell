#include "GameStatus.h"
#include "Screen.h"
#include "raylib.h"
#include <algorithm>

const int BackgroundWidthInPx = 1920;
const int StarshipWidthInPx = 256;
const int StarshipHeightInPx = 256;

GameStatus::GameStatus(Screen* initialScreen) {
    this->isPlaying = false;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->isGoingUp = false;
    this->isGoingDown = false;
    this->isRightBarrelRolling = false;
    this->isLeftBarrelRolling = false;
    this->currentScreen = initialScreen;
    this->currentPosition = { (float)initialScreen->getWidth()/2 - StarshipWidthInPx/2, (float)initialScreen->getHeight() - StarshipHeightInPx };
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
    this->currentPosition = {
        std::max(0.0f, std::min(x, (float)BackgroundWidthInPx - (float)StarshipWidthInPx)),
        std::max(0.0f, std::min(y, (float)this->currentScreen->getHeight() - (float)StarshipWidthInPx))
    };
}

void GameStatus::changeCurrentScreen(Screen *nextScreen) {
    // TODO: Do some kind of transition between screens?
    delete this->currentScreen;
    this->currentScreen = nextScreen;
    if (nextScreen->getType() == ScreenType::Gameplay) this->isPlaying = true;
    if (nextScreen->getType() == ScreenType::Ending) this->isPlaying = false;
}

Vector2 GameStatus::getCurrentPosition() {
    // Gets the current absolute position (this can be out of the window bounds on X axis)
    return this->currentPosition;
}

Vector2 GameStatus::getCurrentScreenPosition() {
    // If X position is less than half the screen width, we set that as X position
    // If it's in between half the screen width and BacgroundWidthInPx - halfWidth we set the X as the center screen
    // If X position is more than BacgroundWidthInPx - halfWidth we set that as the X position
    const int halfWidth = this->getCurrentScreen()->getWidth() / 2;
    const int starshipSpriteCenter = currentPosition.x + StarshipWidthInPx / 2;
    int screenPositionX = this->currentPosition.x;
    const int screenPositionY = this->currentPosition.y;

    if (starshipSpriteCenter <= halfWidth) {}
    else if (starshipSpriteCenter >= halfWidth && starshipSpriteCenter < BackgroundWidthInPx - halfWidth) { screenPositionX = halfWidth - StarshipWidthInPx / 2; }
    else { screenPositionX = halfWidth + this->currentPosition.x - (BackgroundWidthInPx - halfWidth); }

    return { (float)screenPositionX, (float)screenPositionY };
}

bool GameStatus::isPlayerGoingLeft() { return this->isGoingLeft; }
bool GameStatus::isPlayerGoingRight() { return this->isGoingRight; }
bool GameStatus::isPlayerGoingUp() { return this->isGoingUp; }
bool GameStatus::isPlayerGoingDown() { return this->isGoingDown; }
bool GameStatus::isPlayerBarrelRolling() { return this->isPlayerBarrelRollingLeft() || this->isPlayerBarrelRollingRight(); }
bool GameStatus::isPlayerBarrelRollingLeft() { return this->isLeftBarrelRolling; }
bool GameStatus::isPlayerBarrelRollingRight() { return this->isRightBarrelRolling; }

GameStatus::~GameStatus() {
    delete this->currentScreen;
}