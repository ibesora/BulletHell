#include "raylib.h"
#include "LogoScreen.h"
#include "TitleScreen.h"
#include "AssetStore.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 300;
const int FadeOutFramesNum = 60;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

LogoScreen::LogoScreen(int width, int height) : Screen(ScreenType::Logo, width, height) {
    this->currentFrame = 0;
}

void LogoScreen::updateGameStatus() {
    if (this->currentFrame > TotalFramesNum) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height));
    }
}

void LogoScreen::draw() {
    this->currentFrame++;
    ClearBackground(WHITE);
    float alpha;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = (float)this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame < FadeOutStartFramesNum) {
        alpha = 1.0f;
    }
    else {
        alpha = 1.0f - (this->currentFrame - FadeOutStartFramesNum) / (float)FadeOutFramesNum;
    }

    DrawTexture(AssetStore::getInstance().getLogoTexture(), 80.0f, this->height / 2 - 450, Fade(WHITE, alpha));
}