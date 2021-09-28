#include "GameStatus.h"
#include "Screen.h"
#include "raylib.h"
#include "AssetStore.h"
#include <algorithm>

const int RollTimeInMilliseconds = 150;
const int BackgroundWidthInPx = 1920;
const int StarshipWidthInPx = 256;
const int StarshipHeightInPx = 256;
const int CloudsMinSpeed = 5;
const int CloudsMaxSpeed = 10;
const float CloudProbability = 0.015f;

GameStatus::GameStatus(Screen* initialScreen) {
    this->reset(initialScreen);

    //Define special input sequences
    //Barrel rolls
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Released));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Released));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
}

void GameStatus::reset(Screen *screen) {
    this->isPlaying = screen->getType() == ScreenType::Gameplay;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->isGoingUp = false;
    this->isGoingDown = false;
    this->isRightBarrelRolling = false;
    this->isLeftBarrelRolling = false;
    this->currentScreen = screen;
    this->currentPosition = { (float)screen->getWidth() / 2 - StarshipWidthInPx / 2, (float)screen->getHeight() - StarshipHeightInPx };
    this->inputSequence = new InputSequence(3);
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        this->updateInputSequence();
        this->checkBarrelRollSequences();
        this->updateClouds();
    }

    this->getCurrentScreen()->updateGameStatus(this);
}

void GameStatus::checkBarrelRollSequences() {
    if (this->getInputSequence()->checkSequence(this->barrelRollRightKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds))) {
        this->setIsRightBarrelRolling(true);
    }
    else if (this->getInputSequence()->checkSequence(this->barrelRollLeftKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds))) {
        this->setIsLeftBarrelRolling(true);
    }
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
    else if (starshipSpriteCenter > halfWidth && starshipSpriteCenter < BackgroundWidthInPx - halfWidth) { screenPositionX = halfWidth - StarshipWidthInPx / 2; }
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
InputSequence *GameStatus::getInputSequence() { return this->inputSequence; }

void GameStatus::updateInputSequence() {
    if (IsKeyDown(KEY_LEFT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_LEFT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_LEFT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_LEFT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_LEFT);
        }
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_RIGHT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_RIGHT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_RIGHT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_RIGHT);
        }
    }
}

int GameStatus::getCloudsNumber() { return this->cloudPositions.size(); }
int GameStatus::getCloudYPosition(int index) { return this->cloudPositions[index].y; }

GameStatus::~GameStatus() {
    delete this->currentScreen;
    delete this->inputSequence;
}