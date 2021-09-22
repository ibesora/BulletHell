#include "raylib.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"

GameplayScreen::GameplayScreen() : Screen(ScreenType::Gameplay) {
}

void GameplayScreen::updateGameStatus(GameStatus *current) {
    if (IsKeyPressed(KEY_ENTER)) {
        current->changeCurrentScreen(new PauseScreen());
    }
}

void GameplayScreen::draw() {

    ClearBackground(RAYWHITE);
    DrawText("Gameplay Screen", 190, 200, 20, LIGHTGRAY);

}
