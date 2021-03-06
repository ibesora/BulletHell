#include "raylib.h"
#include "Screen.h"
#include "GameStatus.h"
#include "LogoScreen.h"
#include "AssetStore.h"
#include <ctime>

const int ScreenHeight = 1080;
const int ScreenWidth = (int)(ScreenHeight * 0.75); // 810px -> Emulate a 4:3 portrait monitor as the ones used in old shoot'em ups

int main(void) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    InitWindow(ScreenWidth, ScreenHeight, "Bullet Hell");
    SetTargetFPS(60);

    InitAudioDevice();
    AssetStore::getInstance().loadMusic();

    GameStatus::getInstance().setInitialScreen(new LogoScreen(ScreenWidth, ScreenHeight));

    while (!WindowShouldClose()) {
        UpdateMusicStream(GameStatus::getInstance().getCurrentSong());
        GameStatus::getInstance().update();

        BeginDrawing();
        GameStatus::getInstance().getCurrentScreen()->draw();
        EndDrawing();
    }

    AssetStore::getInstance().unloadTextures();
    AssetStore::getInstance().unloadMusic();
    AssetStore::getInstance().unloadFonts();
   
    CloseAudioDevice();

    CloseWindow();

    return 0;
}