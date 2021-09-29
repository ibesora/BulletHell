#pragma once
#include "BulletPattern.h"

class SpiralBulletPattern : public BulletPattern {
public:
    SpiralBulletPattern() : BulletPattern(BulletPatterns::Spiral, 20, 5) {}
    void createBullet(int currentFrame, bool rightTurretActive, bool leftTurretActive,
        Vector2 rightTurretPosition, Vector2 leftTurretPosition, std::vector<GameStatus::BulletInfo> *bullets);
};
#pragma once
