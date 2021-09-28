#include "raylib.h"
#include "Screen.h"
#include "GameStatus.h"
//#include "LogoScreen.h"
#include "GameplayScreen.h"

const int ScreenHeight = 1280;
const int ScreenWidth = ScreenHeight * 0.75; // 960px -> Emulate a 4:3 portrait monitor as the ones used in old shoot'em ups

int main(void) {

    InitWindow(ScreenWidth, ScreenHeight, "Bullet Hell");

    SetTargetFPS(60);

    GameStatus *status = new GameStatus(new GameplayScreen(ScreenWidth, ScreenHeight));

    while (!WindowShouldClose()) {
        status->update();

        BeginDrawing();
        status->getCurrentScreen()->draw(status);
        EndDrawing();
    }

    delete status;
    CloseWindow();

    return 0;
}