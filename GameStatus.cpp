#include "GameStatus.h"
#include "Screen.h"
#include "raylib.h"

GameStatus::GameStatus(Screen* initialScreen) {
    this->isPlaying = false;
    this->wasGoingRight = false;
    this->wasGoingLeft = false;
    this->currentScreen = initialScreen;
    this->currentPosition = { 0.0f, 0.0f };
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        if (IsKeyDown(KEY_RIGHT)) {
            this->wasGoingRight = true;
            this->wasGoingLeft = false;
        }

        if (IsKeyDown(KEY_LEFT)) {
            this->wasGoingRight = false;
            this->wasGoingLeft = true;
        }

        if (IsKeyDown(KEY_UP)) {
        }
        if (IsKeyDown(KEY_DOWN)) {
        }
    }

    this->getCurrentScreen()->updateGameStatus(this);
}

void GameStatus::updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown) {
    this->wasGoingRight = goingRight;
    this->wasGoingLeft = goingLeft;
}

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

bool GameStatus::wasPlayerGoingLeft() { return this->wasGoingLeft; }
bool GameStatus::wasPlayerGoingRight() { return this->wasGoingRight; }

GameStatus::~GameStatus() {
    delete this->currentScreen;
}