#include <cstdlib>
#include "raylib.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputSequence.h"
#include "AssetStore.h"

const int XSpeed = 20;
const int YSpeed = 20;
const int BackgroundSpeed = 5;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 5;
const int MaxInputSequenceDelayInFrames = 45;
const int StarshipWidthInPx = 256;
const int BackgroundWidthInPx = 1920;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    
    this->currentRollFrame = 0;
    this->currentPitchFrame = 0;
    this->currentFrameRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentBackgroundRect = { 0.0f, 0.0f, (float)width, (float)height };
}

void GameplayScreen::updateGameStatus(GameStatus *status) {
    if (IsKeyPressed(KEY_ENTER)) {
        status->changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {
        bool isRollNotCentered = this->currentRollFrame != 0;
        bool isPitchNotCentered = this->currentPitchFrame != 0;
        const Texture2D starshipPitchTexture = AssetStore::getInstance().getStarshipPitchTexture();
        const Texture2D starshipRollTexture = AssetStore::getInstance().getStarshipRollTexture();

        if (IsKeyDown(KEY_UP)) {
            if (status->isPlayerGoingDown()) this->currentPitchFrame = 0;

            status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), true, false);
            status->updatePosition(status->getCurrentPosition().x, status->getCurrentPosition().y - YSpeed);
            this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = (float)starshipPitchTexture.width * 60 - this->currentPitchFrame * (float)starshipPitchTexture.width / 60;
        }
        else if (IsKeyUp(KEY_UP) && status->isPlayerGoingUp() && isPitchNotCentered) {
            this->currentPitchFrame--;
            this->currentFrameRec.x = (float)starshipPitchTexture.width * 60 - this->currentPitchFrame * (float)starshipPitchTexture.width / 60;
            if (this->currentPitchFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), false, status->isPlayerGoingDown());
        }

        if (IsKeyDown(KEY_DOWN)) {
            if (status->isPlayerGoingUp()) this->currentPitchFrame = 0;

            status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), false, true);
            status->updatePosition(status->getCurrentPosition().x, status->getCurrentPosition().y + YSpeed);
            this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = this->currentPitchFrame * (float)starshipPitchTexture.width / 60;
        }
        else if (IsKeyUp(KEY_DOWN) && status->isPlayerGoingDown() && isPitchNotCentered) {
            this->currentPitchFrame--;
            this->currentFrameRec.x = this->currentPitchFrame * (float)starshipPitchTexture.width / 60;
            if (this->currentPitchFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), status->isPlayerGoingUp(), false);
        }

        if (status->isPlayerBarrelRollingRight()) {
            this->currentRollFrame++;
            this->currentFrameRec.x = this->currentRollFrame * (float)starshipRollTexture.width / 60;
            if (this->currentRollFrame == 60) {
                status->setIsRightBarrelRolling(false);
                this->currentRollFrame = 0;
                isRollNotCentered = false;
            }
        }

        if (IsKeyDown(KEY_RIGHT)) {
            if (status->isPlayerGoingLeft() && !status->isPlayerBarrelRollingLeft()) this->currentRollFrame = 0;

            status->updateMovementFlags(true, false, status->isPlayerGoingUp(), status->isPlayerGoingDown());
            status->updatePosition(status->getCurrentPosition().x + XSpeed, status->getCurrentPosition().y);
            if (!status->isPlayerBarrelRolling()) {
                this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
                this->currentFrameRec.x = this->currentRollFrame * (float)starshipRollTexture.width / 60;
            }
        }
        else if (IsKeyUp(KEY_RIGHT) && status->isPlayerGoingRight() && !status->isPlayerBarrelRolling() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = this->currentRollFrame * (float)starshipRollTexture.width / 60;
            if (this->currentRollFrame == 0) status->updateMovementFlags(false, status->isPlayerGoingLeft(), status->isPlayerGoingUp(), status->isPlayerGoingDown());
        }

        if (status->isPlayerBarrelRollingLeft()) {
            this->currentRollFrame++;
            this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - this->currentRollFrame * (float)starshipRollTexture.width / 60;
            if (this->currentRollFrame == 60) {
                status->setIsLeftBarrelRolling(false);
                this->currentRollFrame = 0;
                isRollNotCentered = false;
            }
        }
        
        if (IsKeyDown(KEY_LEFT)) {
            if (status->isPlayerGoingRight() && !status->isPlayerBarrelRollingRight()) this->currentRollFrame = 0;

            status->updateMovementFlags(false, true, status->isPlayerGoingUp(), status->isPlayerGoingDown());
            status->updatePosition(status->getCurrentPosition().x - XSpeed, status->getCurrentPosition().y);
            if (!status->isPlayerBarrelRolling()) {
                this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
                this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - this->currentRollFrame * (float)starshipRollTexture.width / 60;
            }
        }
        else if (IsKeyUp(KEY_LEFT) && status->isPlayerGoingLeft() && !status->isPlayerBarrelRolling() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - this->currentRollFrame * (float)starshipRollTexture.width / 60;
            if (this->currentRollFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), false, status->isPlayerGoingUp(), status->isPlayerGoingDown());
        }

        // Background texture window update
        Vector2 currentPosition = status->getCurrentPosition();
        const int starshipSpriteCenter = (int)currentPosition.x + StarshipWidthInPx / 2;
        const int halfWidth = this->getWidth() / 2;
        if (starshipSpriteCenter <= halfWidth) {
            this->currentBackgroundRect.x = 0.0f;
        }
        else if(starshipSpriteCenter > halfWidth && starshipSpriteCenter < BackgroundWidthInPx - halfWidth) {
            this->currentBackgroundRect.x = (float)(starshipSpriteCenter - halfWidth);
        }
        else {
            this->currentBackgroundRect.x = (float)(BackgroundWidthInPx - this->getWidth());
        }

        this->currentBackgroundRect.y -= (float)BackgroundSpeed;

    }
}

void GameplayScreen::draw(GameStatus *status) {

    ClearBackground(BLACK);
    this->drawBackground();
    this->drawStarship(status);
    this->drawForeground(status);

}

void GameplayScreen::drawBackground() {
    DrawTextureTiled(AssetStore::getInstance().getBackgroundTexture(), this->currentBackgroundRect, { 0.0f, 0.0f, (float)this->width, (float)this->height }, { 0, 0 }, 0.0f, 1.0f, WHITE);
}

void GameplayScreen::drawStarship(GameStatus *status) {
    if ((status->isPlayerGoingUp() || status->isPlayerGoingDown()) && !status->isPlayerGoingRight() && !status->isPlayerGoingLeft()) {
        DrawTextureRec(AssetStore::getInstance().getStarshipPitchTexture(), this->currentFrameRec, status->getCurrentScreenPosition(), WHITE);
    }
    else {
        DrawTextureRec(AssetStore::getInstance().getStarshipRollTexture(), this->currentFrameRec, status->getCurrentScreenPosition(), WHITE);
    }
}

void GameplayScreen::drawForeground(GameStatus *status) {

    const Rectangle rect = { this->currentBackgroundRect.x, 0.0f, (float)this->width, (float)AssetStore::getInstance().getForegroundTexture().height };
    for (int i = 0; i < status->getCloudsNumber(); ++i) {
        DrawTextureRec(AssetStore::getInstance().getForegroundTexture(), rect, { 0.0f, (float)status->getCloudYPosition(i) }, WHITE);
    }

}
