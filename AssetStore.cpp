#include "AssetStore.h"
AssetStore::AssetStore() {
    this->starshipRollTexture = LoadTexture("assets/SF01a_strip60.png");
    this->starshipPitchTexture = LoadTexture("assets/SF01b_strip60.png");
    this->backgroundTexture = LoadTexture("assets/desert-background.png");
    this->foregroundTexture = LoadTexture("assets/clouds.png");
    this->mainEnemyTexture = LoadTexture("assets/enemy_big.png");
    this->powerUpTexture = LoadTexture("assets/powerup.png");
}

AssetStore& AssetStore::getInstance() {
    static AssetStore instance;
    return instance;
}
