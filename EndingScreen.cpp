#include "raylib.h"
#include "EndingScreen.h"
#include "GameplayScreen.h"
#include "TitleScreen.h"
#include "GameStatus.h"
#include "Animations.h"
#include <stdlib.h>

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 0;
const int FadeOutFramesNum = 0;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

EndingScreen::EndingScreen() : Screen(ScreenType::Pause) {
    this->currentFrame = 0;
    this->currentSelectedOption = Option::NextRun;
}

void EndingScreen::updateGameStatus(GameStatus *current) {
    if (this->currentFrame >= TotalFramesNum) {
        const int selectedOption = static_cast<int>(this->currentSelectedOption);
        const int optionNum = static_cast<int>(Option::End);
        if (IsKeyPressed(KEY_DOWN)) this->currentSelectedOption = static_cast<Option>((selectedOption + 1) % optionNum);
        else if (IsKeyPressed(KEY_UP)) this->currentSelectedOption = static_cast<Option>(abs((selectedOption - 1) % optionNum));
        else if (IsKeyPressed(KEY_ENTER)) {
            Screen *nextScreen = this->currentSelectedOption == Option::NextRun ? (Screen *)(new GameplayScreen()) : (Screen *)(new TitleScreen(false));
            current->changeCurrentScreen(nextScreen);
        }
    }
}

void EndingScreen::draw() {
    ClearBackground(BLACK);

    if (this->currentFrame < TotalFramesNum) {
        Animations::FadeText("You died", 190, 330, 20, LIGHTGRAY, currentFrame, FadeInFramesNum, VisibleFramesNum, FadeOutFramesNum);
        this->currentFrame++;
    }
    else {
        DrawText("You died", 190, 330, 20, LIGHTGRAY);
        DrawText(currentSelectedOption == Option::NextRun ? "Try again <-" : "Try again", 190, 350, 20, LIGHTGRAY);
        DrawText(currentSelectedOption == Option::BackToTitle ? "Back to title <-" : "Back to title", 190, 370, 20, LIGHTGRAY);
    }

}