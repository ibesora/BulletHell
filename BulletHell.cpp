#include "raylib.h"
#include "Screen.h"
#include "GameStatus.h"
//#include "LogoScreen.h"
#include "GameplayScreen.h"
#include "AssetStore.h"
#include <ctime>

const int ScreenHeight = 1280;
const int ScreenWidth = ScreenHeight * 0.75; // 960px -> Emulate a 4:3 portrait monitor as the ones used in old shoot'em ups

int main(void) {

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    InitWindow(ScreenWidth, ScreenHeight, "Bullet Hell");
    SetTargetFPS(60);

    GameStatus::getInstance().setInitialScreen(new GameplayScreen(ScreenWidth, ScreenHeight));

    while (!WindowShouldClose()) {
        GameStatus::getInstance().update();

        BeginDrawing();
        GameStatus::getInstance().getCurrentScreen()->draw();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}