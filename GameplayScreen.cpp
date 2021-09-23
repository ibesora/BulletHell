#include "raylib.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"

const int XSpeed = 10;
const int YSpeed = 10;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 10;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->currentFrame = 0;
    this->currentRollFrame = 0;
    this->currentPitchFrame = 0;
    this->starshipRollTexture = LoadTexture("assets/SF01a_strip60.png");
    this->starshipPitchTexture = LoadTexture("assets/SF01b_strip60.png");
    this->currentFrameRec = { 0.0f, 0.0f, (float)starshipRollTexture.width / 60, (float)starshipRollTexture.height };
}

void GameplayScreen::updateGameStatus(GameStatus *status) {
    if (IsKeyPressed(KEY_ENTER)) {
        status->changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {
        Vector2 currentPosition = status->getCurrentPosition();
        bool isRollNotCentered = this->currentRollFrame != 0;
        if (IsKeyDown(KEY_RIGHT)) {
            if (status->wasPlayerGoingLeft()) this->currentRollFrame = 0;
            status->updateMovementFlags(true, false, false, false);
            status->updatePosition(currentPosition.x + XSpeed, currentPosition.y);
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
        }
        else if (IsKeyUp(KEY_RIGHT) && status->wasPlayerGoingRight() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
        }

        if (IsKeyDown(KEY_LEFT)) {
            if (status->wasPlayerGoingRight()) this->currentRollFrame = 0;
            status->updateMovementFlags(false, true, false, false);
            status->updatePosition(currentPosition.x - XSpeed, currentPosition.y);
            this->currentRollFrame += this->currentRollFrame < MaxRollAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = (float)this->starshipRollTexture.width * 60 - this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
        }
        else if (IsKeyUp(KEY_LEFT) && status->wasPlayerGoingLeft() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = (float)this->starshipRollTexture.width * 60 - this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
        }

        if (IsKeyDown(KEY_UP)) {
            status->updateMovementFlags(false, false, true, false);
            status->updatePosition(currentPosition.x, currentPosition.y - YSpeed);
        }
        if (IsKeyDown(KEY_DOWN)) {
            status->updateMovementFlags(false, false, false, true);
            status->updatePosition(currentPosition.x, currentPosition.y + YSpeed);
        }
    }
}

void GameplayScreen::draw(GameStatus *status) {

    ClearBackground(BLACK);
    DrawTextureRec(this->starshipRollTexture, this->currentFrameRec, status->getCurrentPosition(), WHITE);

}
