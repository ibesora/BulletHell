#pragma once
#include "raylib.h"

class AssetStore {
public:
    AssetStore(AssetStore &other) = delete;
    void operator=(const AssetStore &) = delete;
    static AssetStore& getInstance();
    Texture2D getStarshipRollTexture() { return this->starshipRollTexture; }
    Texture2D getStarshipPitchTexture() { return this->starshipPitchTexture; }
    Texture2D getBackgroundTexture() { return this->backgroundTexture; }
    Texture2D getForegroundTexture() { return this->foregroundTexture; }
    Texture2D getMainEnemyTexture() { return this->mainEnemyTexture; }
    Texture2D getPowerUpTexture() { return this->powerUpTexture; }
protected:
    AssetStore();
    Texture2D starshipRollTexture;
    Texture2D starshipPitchTexture;
    Texture2D backgroundTexture;
    Texture2D foregroundTexture;
    Texture2D mainEnemyTexture;
    Texture2D powerUpTexture;
};
