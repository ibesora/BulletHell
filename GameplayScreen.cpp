#include <cstdlib>
#include "raylib.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputHandler.h"
#include "AssetStore.h"

const int StarshipWidthInPx = 256;
const int BackgroundWidthInPx = 1920;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->currentFrameRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentBackgroundRect = { 0.0f, 0.0f, (float)width, (float)height };
}

void GameplayScreen::updateGameStatus() {
    if (IsKeyPressed(KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {

        this->updateStarshipTexture();
        this->updateBackgroundTexture();

    }
}

void GameplayScreen::updateStarshipTexture() {

    bool isRollNotCentered = GameStatus::getInstance().getCurrentRollFrame() != 0;
    bool isPitchNotCentered = GameStatus::getInstance().getCurrentPitchFrame() != 0;
    const Texture2D starshipPitchTexture = AssetStore::getInstance().getStarshipPitchTexture();
    const Texture2D starshipRollTexture = AssetStore::getInstance().getStarshipRollTexture();

    if (InputHandler::getInstance().isKeyDown(KEY_UP)) {
        this->currentFrameRec.x = (float)starshipPitchTexture.width * 60 - GameStatus::getInstance().getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_UP) && GameStatus::getInstance().isPlayerGoingUp() && isPitchNotCentered) {
        this->currentFrameRec.x = (float)starshipPitchTexture.width * 60 - GameStatus::getInstance().getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }

    if (InputHandler::getInstance().isKeyDown(KEY_DOWN)) {
        this->currentFrameRec.x = GameStatus::getInstance().getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_DOWN) && GameStatus::getInstance().isPlayerGoingDown() && isPitchNotCentered) {
        this->currentFrameRec.x = GameStatus::getInstance().getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }

    if (GameStatus::getInstance().isPlayerBarrelRollingRight()) {
        this->currentFrameRec.x = GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }

    if (InputHandler::getInstance().isKeyDown(KEY_RIGHT)) {
        if (!GameStatus::getInstance().isPlayerBarrelRolling()) {
            this->currentFrameRec.x = GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_RIGHT) && GameStatus::getInstance().isPlayerGoingRight() && !GameStatus::getInstance().isPlayerBarrelRolling() && isRollNotCentered) {
        this->currentFrameRec.x = GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }

    if (GameStatus::getInstance().isPlayerBarrelRollingLeft()) {
        this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }

    if (InputHandler::getInstance().isKeyDown(KEY_LEFT)) {
        if (!GameStatus::getInstance().isPlayerBarrelRolling()) {
            this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
        }
    }
    else if (InputHandler::getInstance().isKeyUp(KEY_LEFT) && GameStatus::getInstance().isPlayerGoingLeft() && !GameStatus::getInstance().isPlayerBarrelRolling() && isRollNotCentered) {
        this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - GameStatus::getInstance().getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }
}

void GameplayScreen::updateBackgroundTexture() {
    this->currentBackgroundRect.x = GameStatus::getInstance().getBackgroundPosition().x;
    this->currentBackgroundRect.y = GameStatus::getInstance().getBackgroundPosition().y;
}

void GameplayScreen::draw() {

    ClearBackground(BLACK);
    this->drawBackground();
    this->drawStarship();
    this->drawForeground();

}

void GameplayScreen::drawBackground() {
    DrawTextureTiled(AssetStore::getInstance().getBackgroundTexture(), this->currentBackgroundRect, { 0.0f, 0.0f, (float)this->width, (float)this->height }, { 0, 0 }, 0.0f, 1.0f, WHITE);
}

void GameplayScreen::drawStarship() {
    if ((GameStatus::getInstance().isPlayerGoingUp() || GameStatus::getInstance().isPlayerGoingDown()) && !GameStatus::getInstance().isPlayerGoingRight() && !GameStatus::getInstance().isPlayerGoingLeft()) {
        DrawTextureRec(AssetStore::getInstance().getStarshipPitchTexture(), this->currentFrameRec, GameStatus::getInstance().getCurrentScreenPosition(), WHITE);
    }
    else {
        DrawTextureRec(AssetStore::getInstance().getStarshipRollTexture(), this->currentFrameRec, GameStatus::getInstance().getCurrentScreenPosition(), WHITE);
    }
}

void GameplayScreen::drawForeground() {

    const Rectangle rect = { this->currentBackgroundRect.x, 0.0f, (float)this->width, (float)AssetStore::getInstance().getForegroundTexture().height };
    for (int i = 0; i < GameStatus::getInstance().getCloudsNumber(); ++i) {
        DrawTextureRec(AssetStore::getInstance().getForegroundTexture(), rect, { 0.0f, (float)GameStatus::getInstance().getCloudYPosition(i) }, WHITE);
    }

}
