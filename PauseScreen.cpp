#include "raylib.h"
#include "PauseScreen.h"
#include "TitleScreen.h"
#include "GameplayScreen.h"
#include "GameStatus.h"
#include "TextRenderer.h"
#include "Texts.h"
#include <stdlib.h>

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

    ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::PausedText, 190, 610, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::ContinueText, 190, 630, 20, currentSelectedOption == Option::Continue ? RED : LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::BackToTitleText, 190, 650, 20, currentSelectedOption == Option::BackToTitleScreen ? RED : LIGHTGRAY);

}