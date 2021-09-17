#include "raylib.h"
#include "TitleScreen.h"

TitleScreen::TitleScreen() : Screen(ScreenType::Title) {
}

void TitleScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Title Screen", 190, 200, 20, LIGHTGRAY);

}