#include "raylib.h"
#include "WinScreen.h"

WinScreen::WinScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void WinScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("You won!", 190, 200, 20, LIGHTGRAY);

}