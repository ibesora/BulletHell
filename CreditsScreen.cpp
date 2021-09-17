#include "raylib.h"
#include "CreditsScreen.h"

CreditsScreen::CreditsScreen() : Screen(ScreenType::Credits) {
}

void CreditsScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Credits Screen", 190, 200, 20, LIGHTGRAY);

}