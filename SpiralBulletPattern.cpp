#define _USE_MATH_DEFINES
#include <cmath>
#include "SpiralBulletPattern.h"

void SpiralBulletPattern::createBullet(int currentFrame, bool rightTurretActive, bool leftTurretActive,
    Vector2 rightTurretPosition, Vector2 leftTurretPosition, std::vector<GameStatus::BulletInfo> *bullets) {
    const int numBulletSources = 20;
    const int numPhases = 5;
    for (int i = 0; i < numPhases; ++i) {
        float angle = (currentFrame / numBulletSources % numBulletSources * M_PI / numBulletSources) - i * M_PI / numPhases + M_PI * 0.75;
        if (rightTurretActive) {
            bullets->push_back(GameStatus::BulletInfo({ cos(angle) * this->bulletSpeed, sin(angle) * this->bulletSpeed }, rightTurretPosition));
        }
        if (leftTurretActive) {
            bullets->push_back(GameStatus::BulletInfo({ cos(angle) * this->bulletSpeed, sin(angle) * this->bulletSpeed }, leftTurretPosition));
        }
    }
}