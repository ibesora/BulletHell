#include "raylib.h"
#include "WinScreen.h"
#include "GameplayScreen.h"
#include "TitleScreen.h"
#include "GameStatus.h"
#include "Animations.h"
#include "AssetStore.h"
#include <stdlib.h>
#include "Texts.h"
#include "TextRenderer.h"

const int FadeInFramesNum = 60;
const int VisibleFramesNum = 0;
const int FadeOutFramesNum = 0;
const int FadeOutStartFramesNum = FadeInFramesNum + VisibleFramesNum;
const int TotalFramesNum = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

WinScreen::WinScreen(int width, int height) : Screen(ScreenType::Pause, width, height) {
    this->currentFrame = 0;
}

void WinScreen::updateGameStatus() {
    if (this->currentFrame >= TotalFramesNum) {
        if (IsKeyPressed(KEY_ENTER)) {
            GameStatus::getInstance().reset();
            GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
        }
    }
    else {
        this->currentFrame++;
    }
}

void WinScreen::draw() {
    ClearBackground(BLACK);
    float alpha = 0.0f;
    if (this->currentFrame < FadeInFramesNum) {
        alpha = (float)this->currentFrame / (float)FadeInFramesNum;
    }
    else if (this->currentFrame <= FadeOutStartFramesNum) {
        alpha = 1.0f;
    }

    DrawTexture(AssetStore::getInstance().geYouWonTexture(), 80, this->height / 2 - 400, Fade(WHITE, alpha < 0.01f ? 0.01f : alpha));

    if (this->currentFrame >= FadeOutStartFramesNum) {
        TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, 190, 670, 20, YELLOW);
    }

}