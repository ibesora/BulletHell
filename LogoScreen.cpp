#include "raylib.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "Animations.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 300;
const int FadeOutFramesNum = 60;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

LogoScreen::LogoScreen(int width, int height) : Screen(ScreenType::Logo, width, height) {
    this->currentFrame = 0;
}

void LogoScreen::updateGameStatus(GameStatus *current) {
    if (this->currentFrame > TotalFramesNum) {
        current->changeCurrentScreen(new TitleScreen(this->width, this->height));
    }
}

void LogoScreen::draw(GameStatus *status) {
    currentFrame++;
    ClearBackground(BLACK);
    Animations::FadeText("Logo Screen", 190, 200, 20, LIGHTGRAY, currentFrame, FadeInFramesNum, VisibleFramesNum, FadeOutFramesNum);
}