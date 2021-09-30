#include "raylib.h"
#include "PowerUp.h"
#include "Player.h"

const int YSpeed = 10;
const int FramesPerType = 30;

PowerUp::PowerUp(float x, float y) {
	this->position = { x, y };
	this->lighted = true;
	this->currentFrame = 0;
}

void PowerUp::update() {
	this->currentFrame++;
	if (this->currentFrame == FramesPerType) {
		this->currentFrame = 0;
		this->lighted = !this->lighted;
	}
	this->position.y += (float)YSpeed;
}

Vector2 PowerUp::getPosition() { return this->position; }
int PowerUp::getCurrentFrame() { return this->currentFrame; }
bool PowerUp::isLighted() { return this->lighted; }
