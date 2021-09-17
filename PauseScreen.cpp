#include "raylib.h"
#include "PauseScreen.h"

PauseScreen::PauseScreen() : Screen(ScreenType::Pause) {
}

void PauseScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Pause Screen", 190, 200, 20, LIGHTGRAY);

}