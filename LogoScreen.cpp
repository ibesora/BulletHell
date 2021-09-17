#include "raylib.h"
#include "LogoScreen.h"
#include "TitleScreen.h"

const int FadeInFramesNum = 60;
const int LogoVisibleFramesNum = 300;
const int FadeOutFramesNum = 60;
const int FadeOutStartFramesNum = FadeInFramesNum + LogoVisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + LogoVisibleFramesNum + FadeOutFramesNum;

LogoScreen::LogoScreen() : Screen(ScreenType::Logo) {
    this->currentFrame = 0;
}

void LogoScreen::updateGameStatus(GameStatus *current) {
    if (this->currentFrame > TotalFramesNum) {
        current->changeCurrentScreen(new TitleScreen());
    }
}

void LogoScreen::draw() {
    currentFrame++;
    ClearBackground(BLACK);

    float alpha;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame < FadeOutStartFramesNum) {
        alpha = 1.0;
    }
    else {
        int framesInFadeOut = this->currentFrame - FadeOutStartFramesNum;
        alpha = 1.0 - framesInFadeOut / (float)FadeOutFramesNum;
    }

    // TODO: This must be a texture
    DrawText("Logo Screen", 190, 200, 20, Fade(LIGHTGRAY, alpha));
}