#include "Player.h"
#include "Enemy.h"
#include "InputHandler.h"
#include "AssetStore.h"
#include <algorithm>

const int XSpeed = 20;
const int YSpeed = 20;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 5;
const int FramesPerBullet = 5;
const int BulletSpeed = 15;
const int StarshipWidthInPx = 256;
const int StarshipHeightInPx = 256;
const int BackgroundWidthInPx = 1920;
const int ScreenHeight = 1080;
const int MaxPowerLevel = 3;
const int StartingLife = 1000;
const int DamagePerBullet = 250;
const int GodMode = false;

Player::Player(float x, float y) {
	this->position = { x, y };
	this->updateBoundingTriangle();
	this->beingHit = false;
	this->goingRight = false;
	this->goingLeft = false;
	this->goingUp = false;
	this->goingDown = false;
	this->rightBarrelRolling = false;
	this->leftBarrelRolling = false;
	this->currentRollFrame = 0;
	this->currentPitchFrame = 0;
	this->currentBulletFrame = 0;
    this->powerLevel = 1;
    this->life = StartingLife;
    this->godMode = GodMode;
}

void Player::update(Enemy *enemy) {
	this->updateBullets(enemy);
    this->updateStarship();
}

void Player::updateBullets(Enemy *enemy) {
    std::vector<GameStatus::BulletInfo> aux;
    bool isEnemyBeingHit = false;
    for (int i = 0; i < this->bulletPositions.size(); ++i) {
        GameStatus::BulletInfo current = this->bulletPositions[i];
        this->bulletPositions[i].position = {
            current.position.x + current.speed.x,
            current.position.y + current.speed.y
        };
        if (!enemy->checkCollision(this->bulletPositions[i].position)) {
            aux.push_back(this->bulletPositions[i]);
        }
        else {
            isEnemyBeingHit = true;
        }
    }
    this->bulletPositions = aux;
    enemy->setIsBeingHit(isEnemyBeingHit);
}

void Player::updateStarship() {
    // This handles the starship movement
    bool isRollNotCentered = this->currentRollFrame != 0;
    bool isPitchNotCentered = this->currentPitchFrame != 0;

    if (InputHandler::getInstance().isKeyDown(KEY_UP)) {
        if (this->goingDown) this->currentPitchFrame = 0; // Reset the animation if we are changing directions
        this->updateMovementFlags(this->goingRight, this->goingLeft, true, false);
        this->updatePosition(this->position.x, this->position.y - YSpeed);
        this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_UP) && this->goingUp && isPitchNotCentered) {
        // Even if we have stopped pressing up, we need to run the animation to get back to the initial position
        this->currentPitchFrame--;
        if (this->currentPitchFrame == 0) this->goingUp = false;
    }

    if (InputHandler::getInstance().isKeyDown(KEY_DOWN)) {
        if (this->goingUp) this->currentPitchFrame = 0;
        this->updateMovementFlags(this->goingRight, this->goingLeft, false, true);
        this->updatePosition(this->position.x, this->position.y + YSpeed);
        this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_DOWN) && this->goingDown && isPitchNotCentered) {
        this->currentPitchFrame--;
        if (this->currentPitchFrame == 0) this->goingDown = false;
    }

    if (this->rightBarrelRolling) {
        // When a barrel roll sequence is detected we keep running the animation until it finishes
        this->currentRollFrame++;
        if (this->currentRollFrame == 60) {
            this->rightBarrelRolling = false;
            this->currentRollFrame = 0;
            isRollNotCentered = false;
        }
    }

    if (InputHandler::getInstance().isKeyDown(KEY_RIGHT)) {
        if (this->goingLeft && !this->leftBarrelRolling) this->currentRollFrame = 0;

        this->updateMovementFlags(true, false, this->goingUp, this->goingDown);
        this->updatePosition(this->position.x + XSpeed, this->position.y);
        if (!this->isBarrelRolling()) {
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_RIGHT) && this->goingRight && !this->isBarrelRolling() && isRollNotCentered) {
        this->currentRollFrame--;
        if (this->currentRollFrame == 0) this->updateMovementFlags(false, this->goingLeft, this->goingUp, this->goingDown);
    }

    if (this->leftBarrelRolling) {
        this->currentRollFrame++;
        if (this->currentRollFrame == 60) {
            this->setIsLeftBarrelRolling(false);
            this->currentRollFrame = 0;
            isRollNotCentered = false;
        }
    }

    if (InputHandler::getInstance().isKeyDown(KEY_LEFT)) {
        if (this->goingRight && !this->rightBarrelRolling) this->currentRollFrame = 0;

        this->updateMovementFlags(false, true, this->goingUp, this->goingDown);
        this->updatePosition(this->position.x - XSpeed, this->position.y);
        if (!this->isBarrelRolling()) {
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_LEFT) && this->goingLeft && !this->isBarrelRolling() && isRollNotCentered) {
        this->currentRollFrame--;
        if (this->currentRollFrame == 0) this->updateMovementFlags(this->goingRight, false, this->goingUp, this->goingDown);
    }

    if (InputHandler::getInstance().isKeyDown(KEY_SPACE) && !this->isBarrelRolling()) {
        this->currentBulletFrame++;
        if (this->currentBulletFrame == FramesPerBullet) {
            this->currentBulletFrame = 0;
            this->createBullet();
        }
    }
    else if (InputHandler::getInstance().isKeyReleased(KEY_SPACE) && !this->isBarrelRolling()) {
        this->createBullet();
    }
}

void Player::createBullet() {
    // We create as many bullets as the player power level
    // We also add an offset to the position depending on
    // the power level to simulate a centered shot,
    // two parallel shots or three
    for (int i = 0; i < this->powerLevel; ++i) {
        int offset = 0;
        if (this->powerLevel == 1) offset = 0;
        else if (this->powerLevel == 2) {
            if (i == 0) offset = -10;
            else offset = 10;
        }
        else if (this->powerLevel == 3) {
            if (i == 0) offset = 0;
            else if (i == 1) offset = -20;
            else if (i == 2) offset = 20;
        }

        PlaySound(AssetStore::getInstance().getPlayerLaserSound());
                
        this->bulletPositions.push_back(GameStatus::BulletInfo({ 0.0f, (float)-BulletSpeed }, {
            this->position.x + StarshipWidthInPx / 2 + offset,
            this->position.y + 10
            }));
    }
}

void Player::updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown) {
    this->goingRight = goingRight;
    this->goingLeft = goingLeft;
    this->goingUp = goingUp;
    this->goingDown = goingDown;
}

void Player::setIsRightBarrelRolling(bool rolling) { this->rightBarrelRolling = rolling; }
void Player::setIsLeftBarrelRolling(bool rolling) { this->leftBarrelRolling = rolling; }

void Player::updatePosition(float x, float y) {
    this->position = {
        std::max(0.0f, std::min(x, (float)BackgroundWidthInPx - (float)StarshipWidthInPx)),
        std::max(0.0f, std::min(y, (float)ScreenHeight - (float)StarshipWidthInPx))
    };
    this->updateBoundingTriangle();
}

void Player::updateBoundingTriangle() {
    this->boundingTriangle[0] = { this->position.x + StarshipWidthInPx / 2, this->position.y + 10 };
    this->boundingTriangle[1] = { this->position.x + 30, this->position.y + StarshipHeightInPx - 60 };
    this->boundingTriangle[2] = { this->position.x + StarshipWidthInPx - 30, this->position.y + StarshipHeightInPx - 60 };
}

Vector2 Player::getPosition() { return this->position; }
std::vector<GameStatus::BulletInfo> Player::getBulletPositions() { return this->bulletPositions; }
int Player::getCurrentRollFrame() { return this->currentRollFrame; }
int Player::getCurrentPitchFrame() { return this->currentPitchFrame; }
bool Player::isGoingLeft() { return this->goingLeft; }
bool Player::isGoingRight() { return this->goingRight; }
bool Player::isGoingUp() { return this->goingUp; }
bool Player::isGoingDown() { return this->goingDown; }
bool Player::isBarrelRolling() { return this->isBarrelRollingLeft() || this->isBarrelRollingRight(); }
bool Player::isBarrelRollingLeft() { return this->leftBarrelRolling; }
bool Player::isBarrelRollingRight() { return this->rightBarrelRolling; }

bool Player::checkCollision(Vector2 point) {
    if (this->isBarrelRolling()) return false;
    return CheckCollisionPointTriangle(point, this->boundingTriangle[0], this->boundingTriangle[1], this->boundingTriangle[2]);
}

void Player::setIsBeingHit(bool hit) {
    this->beingHit = hit;
    if (!godMode && hit) {
        PlaySound(AssetStore::getInstance().getPlayerHitSound());
        this->life -= DamagePerBullet;
    }
}

bool Player::isBeingHit() { return this->beingHit; }

void Player::setPowerLevel(int level) { this->powerLevel = level > MaxPowerLevel ? this->powerLevel : level; }
int Player::getPowerLevel() { return this->powerLevel; }
int Player::getLife() { return this->life; }
void Player::setGodMode(bool godMode) { this->godMode = godMode; }