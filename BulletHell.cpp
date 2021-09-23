#include "raylib.h"
#include "Screen.h"
#include "GameStatus.h"
//#include "LogoScreen.h"
#include "GameplayScreen.h"

const int ScreenWidth = 1280;
const int ScreenHeight = 720;

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