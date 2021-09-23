#include "raylib.h"
#include "TitleScreen.h"
#include "GameplayScreen.h"
#include "CreditsScreen.h"
#include "GameStatus.h"
#include "Animations.h"
#include <stdlib.h>

const int TransitionDurationInFrames = 120;

TitleScreen::TitleScreen(int width, int height, const bool shouldAnimate) : Screen(ScreenType::Title, width, height) {
    this->currentFrame = shouldAnimate ? 0 : TransitionDurationInFrames;
    this->currentSelectedOption = Option::StartGame;
}

void TitleScreen::updateGameStatus(GameStatus *current) {
    if (this->currentFrame >= TransitionDurationInFrames) {
        const int selectedOption = static_cast<int>(this->currentSelectedOption);
        const int optionNum = static_cast<int>(Option::End);
        if (IsKeyPressed(KEY_DOWN)) this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
        else if (IsKeyPressed(KEY_UP)) this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
        else if (IsKeyPressed(KEY_ENTER)) {
            Screen *nextScreen = this->currentSelectedOption == Option::StartGame ? (Screen*)(new GameplayScreen(this->width, this->height)) : (Screen*)(new CreditsScreen(this->width, this->height));
            current->changeCurrentScreen(nextScreen);
        }
    }
}

void TitleScreen::draw(GameStatus *status) {

    ClearBackground(RAYWHITE);

    if (this->currentFrame < TransitionDurationInFrames) {
        Animations::MoveText("Title Screen", 20, LIGHTGRAY, 190, 0, 190, 330, currentFrame, TransitionDurationInFrames);
        this->currentFrame++;
    }
    else {
        DrawText("Title Screen", 190, 330, 20, LIGHTGRAY);
        DrawText(currentSelectedOption == Option::StartGame ? "Start Game <-" : "Start Game", 190, 350, 20, LIGHTGRAY);
        DrawText(currentSelectedOption == Option::Credits ? "Credits <-" : "Credits", 190, 370, 20, LIGHTGRAY);
    }

}