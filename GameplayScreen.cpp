#include "raylib.h"
#include "GameplayScreen.h"

GameplayScreen::GameplayScreen() : Screen(ScreenType::Gameplay) {
}

void GameplayScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Gameplay Screen", 190, 200, 20, LIGHTGRAY);

}
