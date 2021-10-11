#include "AssetStore.h"
AssetStore::AssetStore() {
    this->logoTexture = LoadTexture("resources/logo.png");
    this->titleTexture = LoadTexture("resources/title.png");
    this->starshipRollTexture = LoadTexture("resources/SF01a_strip60.png");
    this->starshipPitchTexture = LoadTexture("resources/SF01b_strip60.png");
    this->backgroundTexture = LoadTexture("resources/desert-background.png");
    this->foregroundTexture = LoadTexture("resources/clouds.png");
    this->mainEnemyTexture = LoadTexture("resources/enemy_big.png");
    this->powerUpTexture = LoadTexture("resources/powerup.png");
    this->youWonTexture = LoadTexture("resources/win.png");
    this->youDiedTexture = LoadTexture("resources/lose.png");
    this->menuSong = LoadMusicStream("resources/Loveshadow_-_Stay_Calm_1.mp3");
    this->gameSong = LoadMusicStream("resources/Loveshadow_-_TRANSMUTED_(_N_f_r_)_1.mp3");
    this->playerLaserSound = LoadSound("resources/laserSmall_004.ogg");
    this->powerUpSound = LoadSound("resources/doorOpen_002.ogg");
    this->playerHitSound = LoadSound("resources/impactMetal_004.ogg");
    this->playerDiedSound = LoadSound("resources/explosionCrunch_002.ogg");
    this->customFont = LoadFont("resources/custom.ttf");

    SetMusicVolume(this->menuSong, 0.1f);
    SetMusicVolume(this->gameSong, 0.1f);
    SetSoundVolume(this->playerLaserSound, 0.05f);
    SetSoundVolume(this->powerUpSound, 0.05f);
    SetSoundVolume(this->playerHitSound, 0.3f);
    SetSoundVolume(this->playerDiedSound, 0.5f);
}

void AssetStore::unloadTextures() {
    UnloadTexture(this->logoTexture);
    UnloadTexture(this->titleTexture);
    UnloadTexture(this->starshipRollTexture);
    UnloadTexture(this->starshipPitchTexture);
    UnloadTexture(this->backgroundTexture);
    UnloadTexture(this->foregroundTexture);
    UnloadTexture(this->mainEnemyTexture);
    UnloadTexture(this->powerUpTexture);
    UnloadTexture(this->youWonTexture);
    UnloadTexture(this->youDiedTexture);
}

void AssetStore::loadMusic() {
    PlayMusicStream(this->menuSong);
    PlayMusicStream(this->gameSong);
}

void AssetStore::unloadMusic() {
    UnloadMusicStream(this->menuSong);
    UnloadMusicStream(this->gameSong);
    UnloadSound(this->playerLaserSound);
    UnloadSound(this->powerUpSound);
    UnloadSound(this->playerHitSound);
    UnloadSound(this->playerDiedSound);
}

void AssetStore::unloadFonts() {
    UnloadFont(this->customFont);
}

AssetStore& AssetStore::getInstance() {
    static AssetStore instance;
    return instance;
}
