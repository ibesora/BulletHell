#include "raylib.h"
#include "Screen.h"
#include "GameStatus.h"
#include "LogoScreen.h"

const int ScreenWidth = 1280;
const int ScreenHeight = 720;

int main(void) {

    InitWindow(ScreenWidth, ScreenHeight, "Bullet Hell");

    SetTargetFPS(60);

    GameStatus *status = new GameStatus(new LogoScreen());

    while (!WindowShouldClose()) {
        status->update();

        BeginDrawing();
        status->getCurrentScreen()->draw();
        EndDrawing();
    }

    delete status;
    CloseWindow();

    return 0;
}