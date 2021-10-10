#pragma once
#include "Enemy.h"
#include "Player.h"
#include "AssetStore.h"
#include "CircleBulletPattern.h"
#include "SpiralBulletPattern.h"

const int EnemySpeed = 2;
const int ScreenHeight = 1280;
const int BackgroundWidthInPx = 1920;
const int StarshipWidthInPx = 256;
const int FramesBetweenTurretChanges = 300;
const int FramesBetweenTypeChangeChance = 1000;
const float ChangeBulletPatternProbability = 0.5;
const int StartingLife = 1000;
const int DamagePerBullet = 5;
const int TimeToAppearInFrames = 60 * 23;
const int AppearingAnimationTimeInFrames = 60;

Enemy::Enemy(float x, float y) {
	this->currentBulletPattern = new CircleBulletPattern();
	this->currentDirection = 1;
	this->position = { x, y };
	this->updateBoundingTriangle();
	this->currentFrame = 0;
	this->framesFromStart = 0;
	this->appeared = false;
	this->appearingProgress = 0;
	this->isRightTurretActive = true;
	this->isLeftTurretActive = false;
	this->life = StartingLife;
}

void Enemy::update(Player *player) {
	if(!this->appeared) this->updateAppearingAnimation();
	else {
		this->updatePosition();
		this->updateBullets(player);
	}
}

void Enemy::updateAppearingAnimation() {
	this->framesFromStart++;
	if (this->framesFromStart >= TimeToAppearInFrames) {
		if (this->framesFromStart - TimeToAppearInFrames > AppearingAnimationTimeInFrames) {
			this->framesFromStart = 0;
			this->appeared = true;
		}
		else {
			this->appearingProgress = (float)(this->framesFromStart - TimeToAppearInFrames) / AppearingAnimationTimeInFrames;
		}
	}
}

void Enemy::updatePosition() {
	this->position.x = this->position.x + this->currentDirection * EnemySpeed;
	if (this->position.x < 0 || this->position.x > BackgroundWidthInPx - StarshipWidthInPx) {
		this->currentDirection *= -1;
	}
	this->updateBoundingTriangle();
}

void Enemy::updateBoundingTriangle() {
	this->boundingTriangle[0] = { this->position.x + 256 - 10, this->position.y + 70 };
	this->boundingTriangle[1] = { this->position.x + 10, this->position.y + 70 };
	this->boundingTriangle[2] = { this->position.x + 128, this->position.y + 256 - 30 };
}

void Enemy::updateBullets(Player* player) {
	const int enemyPositionCenter = (int)GameStatus::getInstance().getEnemyPosition().x + AssetStore::getInstance().getMainEnemyTexture().width / 2;
	this->currentFrame++;
	this->updateBulletPosition();
	this->changeBulletPatternThrow();
	this->createBulletIfNeeded();
	this->checkBulletCollisions(player);
}

void Enemy::updateBulletPosition() {
	// Only keep bullets that are inside bounds
	std::vector<GameStatus::BulletInfo> aux;
	for (int i = 0; i < GameStatus::getInstance().getEnemyBulletsNumber(); ++i) {
		GameStatus::BulletInfo bullet = GameStatus::getInstance().getEnemyBullet(i);
		bullet.position = { bullet.position.x + bullet.speed.x, bullet.position.y + bullet.speed.y };
		if ((bullet.position.x > 0 && bullet.position.x < AssetStore::getInstance().getBackgroundTexture().width)
			&& ((bullet.position.y > 0 && bullet.position.y < ScreenHeight))) {
			aux.push_back(bullet);
		}
	}
	this->bulletPositions = aux;
}
void Enemy::changeBulletPatternThrow() {
	if (this->currentFrame == FramesBetweenTypeChangeChance) {
		this->currentFrame = 0;
		const float diceThrow = (float)std::rand() / (float)RAND_MAX;
		if (diceThrow < ChangeBulletPatternProbability) {
			BulletPattern *old = this->currentBulletPattern;
			if (this->currentBulletPattern->getType() == BulletPatterns::Circle) {
				this->currentBulletPattern = new SpiralBulletPattern();
			}
			else {
				this->currentBulletPattern = new CircleBulletPattern();
			}
			delete old;
		}
	}

	if (this->currentFrame % FramesBetweenTurretChanges == 0) {
		if (this->isRightTurretActive && !this->isLeftTurretActive) { this->isRightTurretActive = false; this->isLeftTurretActive = true; }
		else if (!this->isRightTurretActive && this->isLeftTurretActive) { this->isRightTurretActive = true; }
		else if (this->isRightTurretActive && this->isLeftTurretActive) { this->isLeftTurretActive = false; }
	}

}

void Enemy::createBulletIfNeeded() {
	if (this->currentFrame % this->currentBulletPattern->getFramesBetweenWaves() == 0) {
		this->currentBulletPattern->createBullet(this->currentFrame, this->isRightTurretActive, this->isLeftTurretActive,
			this->getRightTurretPosition(), this->getLeftTurretPosition(), &this->bulletPositions);
	}
}

void Enemy::checkBulletCollisions(Player *player) {
	std::vector<GameStatus::BulletInfo> aux;
	bool isEnemyBeingHit = false;
	for (int i = 0; i < this->bulletPositions.size(); ++i) {
		GameStatus::BulletInfo current = this->bulletPositions[i];
		this->bulletPositions[i].position = {
			current.position.x + current.speed.x,
			current.position.y + current.speed.y
		};
		if (!player->checkCollision(this->bulletPositions[i].position)) {
			aux.push_back(this->bulletPositions[i]);
		}
		else {
			isEnemyBeingHit = true;
		}
	}
	this->bulletPositions = aux;
	player->setIsBeingHit(isEnemyBeingHit);
}

Vector2 Enemy::getPosition() {
	return this->position;
}

Vector2 Enemy::getRightTurretPosition() {
	const int enemyPositionCenter = (int)this->position.x + StarshipWidthInPx / 2;
	return { enemyPositionCenter - 15.0f, 150.0f };
}

Vector2 Enemy::getLeftTurretPosition() {
	const int enemyPositionCenter = (int)this->position.x + StarshipWidthInPx / 2;
	return { enemyPositionCenter + 15.0f, 150.0f };
}

std::vector<GameStatus::BulletInfo> Enemy::getBulletPositions() {
	return this->bulletPositions;
}

bool Enemy::checkCollision(Vector2 point) {
	if (!this->appeared) return false;
	return CheckCollisionPointTriangle(point, this->boundingTriangle[0], this->boundingTriangle[1], this->boundingTriangle[2]);
}

void Enemy::setIsBeingHit(bool isHit) {
	this->beingHit = isHit;
	if (isHit) {
		this->life -= DamagePerBullet;
	}
}

bool Enemy::isBeingHit() {
	return this->beingHit;
}

int Enemy::getLife() { return this->life; }
bool Enemy::hasAppeared() { return this->appeared; }
float Enemy::getAppearingProgress() { return this->appearingProgress; }

Enemy::~Enemy() {
	delete this->currentBulletPattern;
}