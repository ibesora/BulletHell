#pragma once
#include "BulletPattern.h"

class CircleBulletPattern: public BulletPattern {
public:
    CircleBulletPattern() : BulletPattern(BulletPatterns::Circle, 60, 5) {}
    void createBullet(int currentFrame, bool rightTurretActive, bool leftTurretActive,
        Vector2 rightTurretPosition, Vector2 leftTurretPosition, std::vector<GameStatus::BulletInfo> *bullets);
};
