#include "AssetStore.h"
AssetStore::AssetStore() {
    this->logoTexture = LoadTexture("assets/logo.png");
    this->titleTexture = LoadTexture("assets/title.png");
    this->starshipRollTexture = LoadTexture("assets/SF01a_strip60.png");
    this->starshipPitchTexture = LoadTexture("assets/SF01b_strip60.png");
    this->backgroundTexture = LoadTexture("assets/desert-background.png");
    this->foregroundTexture = LoadTexture("assets/clouds.png");
    this->mainEnemyTexture = LoadTexture("assets/enemy_big.png");
    this->powerUpTexture = LoadTexture("assets/powerup.png");
    this->youWonTexture = LoadTexture("assets/win.png");
    this->youDiedTexture = LoadTexture("assets/lose.png");
    this->menuSong = LoadMusicStream("assets/Loveshadow_-_Stay_Calm_1.mp3");
    this->gameSong = LoadMusicStream("assets/Loveshadow_-_TRANSMUTED_(_N_f_r_)_1.mp3");
    this->playerLaserSound = LoadSound("assets/laserSmall_004.ogg");
    this->powerUpSound = LoadSound("assets/doorOpen_002.ogg");
    this->playerHitSound = LoadSound("assets/impactMetal_004.ogg");
    this->playerDiedSound = LoadSound("assets/explosionCrunch_002.ogg");

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

AssetStore& AssetStore::getInstance() {
    static AssetStore instance;
    return instance;
}
