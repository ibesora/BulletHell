#pragma once
#include "raylib.h"

class AssetStore {
public:
    AssetStore(AssetStore &other) = delete;
    void operator=(const AssetStore &) = delete;
    static AssetStore& getInstance();
    Texture2D getLogoTexture() { return this->logoTexture; }
    Texture2D getTitleTexture() { return this->titleTexture; }
    Texture2D getStarshipRollTexture() { return this->starshipRollTexture; }
    Texture2D getStarshipPitchTexture() { return this->starshipPitchTexture; }
    Texture2D getBackgroundTexture() { return this->backgroundTexture; }
    Texture2D getForegroundTexture() { return this->foregroundTexture; }
    Texture2D getMainEnemyTexture() { return this->mainEnemyTexture; }
    Texture2D getPowerUpTexture() { return this->powerUpTexture; }
    Texture2D geYouWonTexture() { return this->youWonTexture; }
    Texture2D getYouDiedTexture() { return this->youDiedTexture; }
    Music getMenuSong() { return this->menuSong; }
    Music getGameSong() { return this->gameSong; }
    Sound getPlayerLaserSound() { return this->playerLaserSound; }
    Sound getPowerUpSound() { return this->powerUpSound; }
    Sound getPlayerHitSound() { return this->playerHitSound; }
    Sound getPlayerDiedSound() { return this->playerDiedSound; }
    Font getCustomFont() { return this->customFont; }
    void unloadTextures();
    void unloadFonts();
    void loadMusic();
    void unloadMusic();
protected:
    AssetStore();
    Texture2D logoTexture;
    Texture2D titleTexture;
    Texture2D starshipRollTexture;
    Texture2D starshipPitchTexture;
    Texture2D backgroundTexture;
    Texture2D foregroundTexture;
    Texture2D mainEnemyTexture;
    Texture2D powerUpTexture;
    Texture2D youWonTexture;
    Texture2D youDiedTexture;
    Music menuSong;
    Music gameSong;
    Sound playerLaserSound;
    Sound powerUpSound;
    Sound playerHitSound;
    Sound playerDiedSound;
    Font customFont;
};
