#include "GameStatus.h"
#include "Screen.h"

GameStatus::GameStatus(Screen* initialScreen) {
    this->currentScreen = initialScreen;
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {
    this->getCurrentScreen()->updateGameStatus(this);
}

void GameStatus::changeCurrentScreen(Screen *nextScreen) {
    // TODO: Do some kind of transition between screens?
    delete this->currentScreen;
    this->currentScreen = nextScreen;
}

GameStatus::~GameStatus() {
    delete this->currentScreen;
}