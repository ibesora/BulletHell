#pragma once
#include "raylib.h"
#include "GameStatus.h"

class Enemy;

class Player {
public:
	Player(float x, float y);
	void update(Enemy *enemy);
	Vector2 getPosition();
	std::vector<GameStatus::BulletInfo> getBulletPositions();
	bool checkCollision(Vector2 point);
	void setIsBeingHit(bool);
	bool isBeingHit();
	void setIsRightBarrelRolling(bool);
	void setIsLeftBarrelRolling(bool);
	int getCurrentRollFrame();
	int getCurrentPitchFrame();
	bool isGoingRight();
	bool isGoingLeft();
	bool isGoingUp();
	bool isGoingDown();
	bool isBarrelRolling();
	bool isBarrelRollingRight();
	bool isBarrelRollingLeft();
	void setPowerLevel(int);
	int getPowerLevel();
protected:
	void updateStarship();
	void updateBoundingTriangle();
	void updateBullets(Enemy *enemy);
	void updateMovementFlags(bool goingRight, bool goingLeft, bool goingUp, bool goingDown);
	void updatePosition(float x, float y);
	void createBullet();

	Vector2 position;
	Vector2 boundingTriangle[3];
	bool beingHit;
	std::vector<GameStatus::BulletInfo> bulletPositions;
	bool goingRight;
	bool goingLeft;
	bool goingUp;
	bool goingDown;
	bool rightBarrelRolling;
	bool leftBarrelRolling;
	int currentRollFrame;
	int currentPitchFrame;
	int currentBulletFrame;
	int powerLevel;
};