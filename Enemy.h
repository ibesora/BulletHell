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
	~Enemy();
protected:
	void updatePosition();
	void updateBulletPosition();
	void updateBullets();
	void changeBulletPatternThrow();
	void createBulletIfNeeded();
	Vector2 getRightTurretPosition();
	Vector2 getLeftTurretPosition();

	BulletPattern *currentBulletPattern;
	int currentDirection;
	Vector2 position;
	int currentFrame;
	bool isRightTurretActive;
	bool isLeftTurretActive;
	std::vector<GameStatus::BulletInfo> bulletPositions;
};