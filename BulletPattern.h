#pragma once
#include "GameStatus.h"

enum class BulletPatterns : int { Circle, Spiral };

class BulletPattern {
public:
    BulletPattern(BulletPatterns type, int framesBetweenWaves, int bulletSpeed) {
        this->type = type;
        this->framesBetweenWaves = framesBetweenWaves;
        this->bulletSpeed = bulletSpeed;
    };

    BulletPatterns getType() { return this->type; }
    int getFramesBetweenWaves() { return this->framesBetweenWaves; }
    virtual void createBullet(int currentFrame, bool rightTurretActive, bool leftTurretActive,
        Vector2 rightTurretPosition, Vector2 leftTurretPosition, std::vector<GameStatus::BulletInfo> *bullets) = 0;

protected:
    BulletPatterns type;
    int framesBetweenWaves;
    int bulletSpeed;
};
