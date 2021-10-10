#define _USE_MATH_DEFINES
#include <cmath>
#include "CircleBulletPattern.h"

void CircleBulletPattern::createBullet(int currentFrame, bool rightTurretActive, bool leftTurretActive,
    Vector2 rightTurretPosition, Vector2 leftTurretPosition, std::vector<GameStatus::BulletInfo> *bullets) {
    const int numBulletSources = 10;
    for (int i = 0; i <= numBulletSources; ++i) {
        float angle = (float)(i * M_PI / numBulletSources);
        if (rightTurretActive) {
            bullets->push_back(GameStatus::BulletInfo({ cos(angle) * this->bulletSpeed, sin(angle) * this->bulletSpeed }, rightTurretPosition));
        }
        if (leftTurretActive) {
            bullets->push_back(GameStatus::BulletInfo({ cos(angle) * this->bulletSpeed, sin(angle) * this->bulletSpeed }, leftTurretPosition));
        }
    }
}