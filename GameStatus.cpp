#include "GameStatus.h"
#include "Screen.h"
#include "raylib.h"
#include "AssetStore.h"
#include "InputHandler.h"
#include <algorithm>

const int XSpeed = 20;
const int YSpeed = 20;
const int BackgroundSpeed = 5;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 5;
const int BackgroundWidthInPx = 1920;
const int StarshipWidthInPx = 256;
const int StarshipHeightInPx = 256;
const int CloudsMinSpeed = 5;
const int CloudsMaxSpeed = 10;
const float CloudProbability = 0.015f;
const int FramesPerBullet = 5;
const int BulletSpeed = 15;

GameStatus::GameStatus() {
    this->isPlaying = false;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->isGoingUp = false;
    this->isGoingDown = false;
    this->isRightBarrelRolling = false;
    this->isLeftBarrelRolling = false;
    this->currentPosition = { 0.0f, 0.0f };
    this->currentScreen = nullptr;
    this->currentRollFrame = 0;
    this->currentPitchFrame = 0;
    this->currentBulletFrame = 0;
}

GameStatus &GameStatus::getInstance() {
    static GameStatus instance;
    return instance;
}

void GameStatus::setInitialScreen(Screen* initialScreen) {
    this->currentScreen = initialScreen;
    this->reset();
}

void GameStatus::reset() {
    this->isPlaying = this->currentScreen->getType() == ScreenType::Gameplay;
    this->isGoingRight = false;
    this->isGoingLeft = false;
    this->isGoingUp = false;
    this->isGoingDown = false;
    this->isRightBarrelRolling = false;
    this->isLeftBarrelRolling = false;
    this->currentRollFrame = 0;
    this->currentPitchFrame = 0;
    this->currentPosition = { (float)this->currentScreen->getWidth() / 2 - StarshipWidthInPx / 2, (float)this->currentScreen->getHeight() - StarshipHeightInPx };
    this->cloudPositions.clear();
    this->bulletPositions.clear();
    InputHandler::getInstance().reset();
}

Screen* GameStatus::getCurrentScreen() {
    return this->currentScreen;
}

void GameStatus::update() {

    if (this->isPlaying) {
        this->updateInputs();
        this->updateBullets();
        this->updateStarship();
        this->updateEnemies();
        this->updateBackground();
        this->updateClouds();
    }

    this->getCurrentScreen()->updateGameStatus();
}

void GameStatus::updateInputs() {
    InputHandler::getInstance().update();
    if (InputHandler::getInstance().checkRightBarrelRoll()) this->setIsRightBarrelRolling(true);
    else if (InputHandler::getInstance().checkLeftBarrelRoll()) this->setIsLeftBarrelRolling(true);
}

void GameStatus::updateBullets() {
    for (int i = 0; i < this->bulletPositions.size(); ++i) {
        BulletInfo current = this->bulletPositions[i];
        this->bulletPositions[i].position = {
            current.position.x + current.speed.x,
            current.position.y + current.speed.y
        };
    }
}

void GameStatus::updateStarship() {
    // This handles the starship movement
    bool isRollNotCentered = this->currentRollFrame != 0;
    bool isPitchNotCentered = this->currentPitchFrame != 0;

    if (InputHandler::getInstance().isKeyDown(KEY_UP)) {
        if (this->isGoingDown) this->currentPitchFrame = 0; // Reset the animation if we are changing directions
        this->updateMovementFlags(this->isGoingRight, this->isGoingLeft, true, false);
        this->updatePosition(this->currentPosition.x, this->currentPosition.y - YSpeed);
        this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_UP) && this->isGoingUp && isPitchNotCentered) {
        // Even if we have stopped pressing up, we need to run the animation to get back to the initial position
        this->currentPitchFrame--;
        if (this->currentPitchFrame == 0) this->isGoingUp = false;
    }

    if (InputHandler::getInstance().isKeyDown(KEY_DOWN)) {
        if (this->isGoingUp) this->currentPitchFrame = 0;
        this->updateMovementFlags(this->isGoingRight, this->isGoingLeft, false, true);
        this->updatePosition(this->currentPosition.x, this->currentPosition.y + YSpeed);
        this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_DOWN) && this->isGoingDown && isPitchNotCentered) {
        this->currentPitchFrame--;
        if (this->currentPitchFrame == 0) this->isGoingDown = false;
    }

    if (this->isRightBarrelRolling) {
        // When a barrel roll sequence is detected we keep running the animation until it finishes
        this->currentRollFrame++;
        if (this->currentRollFrame == 60) {
            this->isRightBarrelRolling = false;
            this->currentRollFrame = 0;
            isRollNotCentered = false;
        }
    }

    if (InputHandler::getInstance().isKeyDown(KEY_RIGHT)) {
        if (this->isGoingLeft && !this->isLeftBarrelRolling) this->currentRollFrame = 0;

        this->updateMovementFlags(true, false, this->isGoingUp, this->isGoingDown);
        this->updatePosition(this->currentPosition.x + XSpeed, this->currentPosition.y);
        if (!this->isPlayerBarrelRolling()) {
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_RIGHT) && this->isGoingRight && !this->isPlayerBarrelRolling() && isRollNotCentered) {
        this->currentRollFrame--;
        if (this->currentRollFrame == 0) this->updateMovementFlags(false, this->isGoingLeft, this->isGoingUp, this->isGoingDown);
    }

    if (this->isLeftBarrelRolling) {
        this->currentRollFrame++;
        if (this->currentRollFrame == 60) {
            this->setIsLeftBarrelRolling(false);
            this->currentRollFrame = 0;
            isRollNotCentered = false;
        }
    }

    if (InputHandler::getInstance().isKeyDown(KEY_LEFT)) {
        if (this->isGoingRight && !this->isRightBarrelRolling) this->currentRollFrame = 0;

        this->updateMovementFlags(false, true, this->isGoingUp, this->isGoingDown);
        this->updatePosition(this->currentPosition.x - XSpeed, this->currentPosition.y);
        if (!this->isPlayerBarrelRolling()) {
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_LEFT) && this->isGoingLeft && !this->isPlayerBarrelRolling() && isRollNotCentered) {
        this->currentRollFrame--;
        if (this->currentRollFrame == 0) this->updateMovementFlags(this->isGoingRight, false, this->isGoingUp, this->isGoingDown);
    }

    if (InputHandler::getInstance().isKeyDown(KEY_SPACE) && !this->isPlayerBarrelRolling()) {
        this->currentBulletFrame++;
        if (this->currentBulletFrame == FramesPerBullet) {
            this->currentBulletFrame = 0;
            this->createBullet();
        }
    }
    else if (InputHandler::getInstance().isKeyReleased(KEY_SPACE) && !this->isPlayerBarrelRolling()) {
        this->createBullet();
    }
}

void GameStatus::updateEnemies() {

}

void GameStatus::createBullet() {
    this->bulletPositions.push_back(BulletInfo({ 0.0f, (float)-BulletSpeed }, {
        this->currentPosition.x + StarshipWidthInPx / 2,
        this->currentPosition.y + 10
        }));
}

void GameStatus::updateBackground() {
    // The background is bigger than the game window so we need to compute which part of
    // the background we need to draw. Basically the background is constantly scrolling
    // down and is moved right/left depending on the player position
    const int starshipSpriteCenter = (int)this->currentPosition.x + StarshipWidthInPx / 2;
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
    this->isPlaying = (this->currentScreen->getType() == ScreenType::Gameplay);
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

Vector2 GameStatus::getBackgroundPosition() { return this->backgroundPosition; }

int GameStatus::getCurrentRollFrame() { return this->currentRollFrame; }
int GameStatus::getCurrentPitchFrame() { return this->currentPitchFrame; }

bool GameStatus::isPlayerGoingLeft() { return this->isGoingLeft; }
bool GameStatus::isPlayerGoingRight() { return this->isGoingRight; }
bool GameStatus::isPlayerGoingUp() { return this->isGoingUp; }
bool GameStatus::isPlayerGoingDown() { return this->isGoingDown; }
bool GameStatus::isPlayerBarrelRolling() { return this->isPlayerBarrelRollingLeft() || this->isPlayerBarrelRollingRight(); }
bool GameStatus::isPlayerBarrelRollingLeft() { return this->isLeftBarrelRolling; }
bool GameStatus::isPlayerBarrelRollingRight() { return this->isRightBarrelRolling; }
int GameStatus::getCloudsNumber() { return this->cloudPositions.size(); }
int GameStatus::getCloudYPosition(int index) { return this->cloudPositions[index].y; }

int GameStatus::getBulletsNumber() { return this->bulletPositions.size(); }
GameStatus::BulletInfo GameStatus::getBullet(int index) { return this->bulletPositions[index]; }

GameStatus::~GameStatus() {
    delete this->currentScreen;
}