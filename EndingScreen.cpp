#include "raylib.h"
#include "EndingScreen.h"

EndingScreen::EndingScreen() : Screen(ScreenType::Ending) {
}

void EndingScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Ending Screen", 190, 200, 20, LIGHTGRAY);

}