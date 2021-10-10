#include "raylib.h"
#include "HowToPlayScreen.h"
#include "Texts.h"
#include "InputHandler.h"
#include "GameStatus.h"
#include "TitleScreen.h"
#include "AssetStore.h"
#include <algorithm>
#include "TextRenderer.h"

const int MaxAnimationInFrames = 60;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 5;

HowToPlayScreen::HowToPlayScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
    this->currentFrame = 0;
    this->currentPitchUpAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipPitchTexture().width / 60, (float)AssetStore::getInstance().getStarshipPitchTexture().height };
    this->currentPitchDownAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipPitchTexture().width / 60, (float)AssetStore::getInstance().getStarshipPitchTexture().height };
    this->currentRollRightAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentRollLeftAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentBarrelRollLeftAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentBarrelRollRightAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentPowerUpAnimRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getPowerUpTexture().width / 2, (float)AssetStore::getInstance().getPowerUpTexture().height };
}

void HowToPlayScreen::updateGameStatus() {
    this->currentFrame++;
    const int currentFrame = this->currentFrame / 2;
    const Texture2D starshipPitchTexture = AssetStore::getInstance().getStarshipPitchTexture();
    const Texture2D starshipRollTexture = AssetStore::getInstance().getStarshipRollTexture();
    if (currentFrame == MaxAnimationInFrames) this->currentFrame = 0;

    this->currentPitchUpAnimRec.x = (float)starshipPitchTexture.width * 60 - std::min(currentFrame, MaxPitchAnimationFrame) * (float)starshipPitchTexture.width / 60;
    this->currentPitchDownAnimRec.x = std::min(currentFrame, MaxPitchAnimationFrame) * (float)starshipPitchTexture.width / 60;
    this->currentRollLeftAnimRec.x = (float)starshipRollTexture.width * 60 - std::min(currentFrame, MaxRollAnimationFrame) * (float)starshipRollTexture.width / 60;
    this->currentRollRightAnimRec.x = std::min(currentFrame, MaxRollAnimationFrame) * (float)starshipRollTexture.width / 60;
    this->currentBarrelRollLeftAnimRec.x = (float)starshipRollTexture.width * 60 - currentFrame * (float)starshipRollTexture.width / 60;
    this->currentBarrelRollRightAnimRec.x = currentFrame * (float)starshipRollTexture.width / 60;
    this->currentPowerUpAnimRec.x = currentFrame < MaxAnimationInFrames / 2 ? 0.0f : 64.0f;


    if (InputHandler::getInstance().isKeyPressed(KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
    }
}

void HowToPlayScreen::draw() {

    const int left = 90;
    const int right = this->width - 90;
    const int bottomMargin = 90;
    const int textSize = 20;
    const int starshipHeight = 128;
    const int starshipHalfHeight = starshipHeight / 2;
    const int starshipWidth = 128;
    const int powerupHeight = 64;
    const int powerupHalfHeight = 32;
    int top = textSize;

    ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::Controls, left, top, textSize, YELLOW);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::GoUp, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipPitchTexture(), this->currentPitchUpAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::GoDown, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipPitchTexture(), this->currentPitchDownAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::GoLeft, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipRollTexture(), this->currentRollLeftAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::GoRight, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipRollTexture(), this->currentRollRightAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::BarrelRollLeft, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipRollTexture(), this->currentBarrelRollLeftAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::BarrelRollRight, left, top + starshipHalfHeight, textSize, LIGHTGRAY);
    DrawTextureTiled(AssetStore::getInstance().getStarshipRollTexture(), this->currentBarrelRollRightAnimRec, { (float)right - starshipWidth, (float)top, 128.0f, 128.0f }, { 0.0f, 0.0f }, 0, 0.5, WHITE);
    top += textSize + starshipHeight;
    TextRenderer::getInstance().draw(Texts::Shoot, left, top, textSize, LIGHTGRAY);
    top += textSize + powerupHalfHeight;
    TextRenderer::getInstance().draw(Texts::GetPowerup, left, top + powerupHalfHeight, textSize, LIGHTGRAY);
    DrawTextureRec(AssetStore::getInstance().getPowerUpTexture(), this->currentPowerUpAnimRec, { (float)right - powerupHeight - powerupHalfHeight, (float)top }, WHITE);
    top += textSize + powerupHeight;
    TextRenderer::getInstance().draw(Texts::MissionTitle, left, top, textSize, YELLOW);
    top += textSize;
    TextRenderer::getInstance().draw(Texts::MissionText, left, top, textSize * 2, RED);
    top = this->height - bottomMargin;
    TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, left * 3, top, textSize, YELLOW);

}