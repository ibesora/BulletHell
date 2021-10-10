#include "raylib.h"
#include "PauseScreen.h"
#include "TitleScreen.h"
#include "GameplayScreen.h"
#include "GameStatus.h"
#include <stdlib.h>
#include "TextRenderer.h"

PauseScreen::PauseScreen(int width, int height) : Screen(ScreenType::Pause, width, height) {
    this->currentSelectedOption = Option::Continue;
}

void PauseScreen::updateGameStatus() {
    const int selectedOption = static_cast<int>(this->currentSelectedOption);
    const int optionNum = static_cast<int>(Option::End);
    if (IsKeyPressed(KEY_DOWN)) {
        this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
    }
    else if (IsKeyPressed(KEY_UP)) {
        this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
    }
    else if (IsKeyPressed(KEY_ENTER)) {
        Screen *nextScreen = this->currentSelectedOption == Option::Continue ? (Screen *)(new GameplayScreen(this->width, this->height)) : (Screen *)(new TitleScreen(this->width, this->height, false));
        GameStatus::getInstance().changeCurrentScreen(nextScreen);
    }
}

void PauseScreen::draw() {

    ClearBackground(RAYWHITE);
    TextRenderer::getInstance().draw("Pause Screen", 190, 330, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(currentSelectedOption == Option::Continue? "Continue <-" : "Continue", 190, 350, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(currentSelectedOption == Option::BackToTitleScreen ? "Back to title <-" : "Back to title", 190, 370, 20, LIGHTGRAY);

}