#pragma once
#include "raylib.h"
#include "GameStatus.h"

class BulletPattern;

class Enemy {
public:
	Enemy(float x, float y);
	void update();
	Vector2 getPosition();
	std::vector<GameStatus::BulletInfo> getBulletPositions();
	bool checkCollision(Vector2 point);
	void setIsBeingHit(bool);
	bool isBeingHit();
	~Enemy();
protected:
	void updatePosition();
	void updateBoundingTriangle();
	void updateBulletPosition();
	void updateBullets();
	void changeBulletPatternThrow();
	void createBulletIfNeeded();
	Vector2 getRightTurretPosition();
	Vector2 getLeftTurretPosition();

	BulletPattern *currentBulletPattern;
	int currentDirection;
	Vector2 position;
	Vector2 boundingTriangle[3];
	int currentFrame;
	bool isRightTurretActive;
	bool isLeftTurretActive;
	bool beingHit;
	std::vector<GameStatus::BulletInfo> bulletPositions;
};