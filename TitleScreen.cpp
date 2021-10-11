#include "raylib.h"
#include "TitleScreen.h"
#include "GameplayScreen.h"
#include "CreditsScreen.h"
#include "HowToPlayScreen.h"
#include "GameStatus.h"
#include "AssetStore.h"
#include "Texts.h"
#include <stdlib.h>
#include "TextRenderer.h"

const int TransitionDurationInFrames = 30;

TitleScreen::TitleScreen(int width, int height, const bool shouldAnimate) : Screen(ScreenType::Title, width, height) {
    this->currentFrame = shouldAnimate ? 0 : TransitionDurationInFrames;
    this->currentSelectedOption = Option::StartGame;
}

void TitleScreen::updateGameStatus() {
    if (this->currentFrame >= TransitionDurationInFrames) {
        const int selectedOption = static_cast<int>(this->currentSelectedOption);
        const int optionNum = static_cast<int>(Option::End);
        if (IsKeyPressed(KEY_DOWN)) {
            this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
        }
        else if (IsKeyPressed(KEY_UP)) {
            this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
        }
        else if (IsKeyPressed(KEY_ENTER)) {
            Screen *nextScreen;
            if (this->currentSelectedOption == Option::StartGame) {
                nextScreen = (Screen *)(new GameplayScreen(this->width, this->height));
                GameStatus::getInstance().reset();
            }
            else if (this->currentSelectedOption == Option::HowToPlay) {
                nextScreen = (Screen *)(new HowToPlayScreen(this->width, this->height));
            }
            else {
                nextScreen = (Screen *)(new CreditsScreen(this->width, this->height));
            }
            GameStatus::getInstance().changeCurrentScreen(nextScreen);
        }
    }
}

void TitleScreen::draw() {

    ClearBackground(BLACK);

    if (this->currentFrame < TransitionDurationInFrames) {
        DrawTexture(AssetStore::getInstance().getTitleTexture(), 5, (int)((this->height / 2 - 400) * currentFrame / (float)TransitionDurationInFrames), WHITE);
        this->currentFrame++;
    }
    else {
        DrawTexture(AssetStore::getInstance().getTitleTexture(), 5, this->height / 2 - 400, WHITE);
        TextRenderer::getInstance().draw(Texts::StartGame, 190, 650, 20, currentSelectedOption == Option::StartGame ? RED : WHITE);
        TextRenderer::getInstance().draw(Texts::HowToPlay, 190, 670, 20, currentSelectedOption == Option::HowToPlay ? RED : WHITE);
        TextRenderer::getInstance().draw(Texts::Credits, 190, 690, 20, currentSelectedOption == Option::Credits ? RED : WHITE);
        TextRenderer::getInstance().draw(Texts::PressEnterToSelect, 190, 730, 20, YELLOW);
        TextRenderer::getInstance().draw(Texts::PressEscToQuit, 190, 750, 20, YELLOW);
    }

}