#pragma once
#include "raylib.h"

class Player;

class PowerUp {
public:
	PowerUp(float x, float y);
	void update();
	Vector2 getPosition();
	int getCurrentFrame();
	bool isLighted();
protected:

	bool lighted;
	Vector2 position;
	int currentFrame;
};