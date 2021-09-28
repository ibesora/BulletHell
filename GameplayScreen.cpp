#include "raylib.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputSequence.h"

const int XSpeed = 20;
const int YSpeed = 20;
const int BackgroundSpeed = 5;
const int MaxRollAnimationFrame = 10;
const int MaxPitchAnimationFrame = 5;
const int MaxInputSequenceDelayInFrames = 45;
const int RollTimeInMilliseconds = 150;
const int StarshipWidthInPx = 256;
const int BackgroundWidthInPx = 1920;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->inputSequenceFrame = 0;
    this->inputSequence = new InputSequence(3);
    this->currentRollFrame = 0;
    this->currentPitchFrame = 0;
    this->starshipRollTexture = LoadTexture("assets/SF01a_strip60.png");
    this->starshipPitchTexture = LoadTexture("assets/SF01b_strip60.png");
    this->backgroundTexture = LoadTexture("assets/desert-background.png");
    this->foregroundTexture = LoadTexture("assets/clouds.png");
    this->currentFrameRec = { 0.0f, 0.0f, (float)starshipRollTexture.width / 60, (float)starshipRollTexture.height };
    this->currentBackgroundRect = { 0.0f, 0.0f, (float)width, (float)height };

    //Define special input sequences
    //Barrel rolls
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Released));
    this->barrelRollRightKeySequence.push_back(InputSequence::Input(KEY_RIGHT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Released));
    this->barrelRollLeftKeySequence.push_back(InputSequence::Input(KEY_LEFT, InputSequence::KeyStatus::Pressed));
}

void GameplayScreen::updateGameStatus(GameStatus *status) {
    if (IsKeyPressed(KEY_ENTER)) {
        status->changeCurrentScreen(new PauseScreen(this->width, this->height));
    }
    else {
        bool isRollNotCentered = this->currentRollFrame != 0;
        bool isPitchNotCentered = this->currentPitchFrame != 0;

        this->updateInputSequence();
        if (this->inputSequence->checkSequence(this->barrelRollRightKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds))) {
            status->setIsRightBarrelRolling(true);
        }
        else if (this->inputSequence->checkSequence(this->barrelRollLeftKeySequence, std::chrono::milliseconds(RollTimeInMilliseconds))) {
            status->setIsLeftBarrelRolling(true);
        }

        if (IsKeyDown(KEY_UP)) {
            if (status->isPlayerGoingDown()) this->currentPitchFrame = 0;

            status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), true, false);
            status->updatePosition(status->getCurrentPosition().x, status->getCurrentPosition().y - YSpeed);
            this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = (float)this->starshipPitchTexture.width * 60 - this->currentPitchFrame * (float)this->starshipPitchTexture.width / 60;
        }
        else if (IsKeyUp(KEY_UP) && status->isPlayerGoingUp() && isPitchNotCentered) {
            this->currentPitchFrame--;
            this->currentFrameRec.x = (float)this->starshipPitchTexture.width * 60 - this->currentPitchFrame * (float)this->starshipPitchTexture.width / 60;
            if (this->currentPitchFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), false, status->isPlayerGoingDown());
        }

        if (IsKeyDown(KEY_DOWN)) {
            if (status->isPlayerGoingUp()) this->currentPitchFrame = 0;

            status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), false, true);
            status->updatePosition(status->getCurrentPosition().x, status->getCurrentPosition().y + YSpeed);
            this->currentPitchFrame += this->currentPitchFrame < MaxPitchAnimationFrame ? 1 : 0;
            this->currentFrameRec.x = this->currentPitchFrame * (float)this->starshipPitchTexture.width / 60;
        }
        else if (IsKeyUp(KEY_DOWN) && status->isPlayerGoingDown() && isPitchNotCentered) {
            this->currentPitchFrame--;
            this->currentFrameRec.x = this->currentPitchFrame * (float)this->starshipPitchTexture.width / 60;
            if (this->currentPitchFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), status->isPlayerGoingLeft(), status->isPlayerGoingUp(), false);
        }

        if (status->isPlayerBarrelRollingRight()) {
            this->currentRollFrame++;
            this->currentFrameRec.x = this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
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
                this->currentFrameRec.x = this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
            }
        }
        else if (IsKeyUp(KEY_RIGHT) && status->isPlayerGoingRight() && !status->isPlayerBarrelRolling() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
            if (this->currentRollFrame == 0) status->updateMovementFlags(false, status->isPlayerGoingLeft(), status->isPlayerGoingUp(), status->isPlayerGoingDown());
        }

        if (status->isPlayerBarrelRollingLeft()) {
            this->currentRollFrame++;
            this->currentFrameRec.x = (float)this->starshipRollTexture.width * 60 - this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
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
                this->currentFrameRec.x = (float)this->starshipRollTexture.width * 60 - this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
            }
        }
        else if (IsKeyUp(KEY_LEFT) && status->isPlayerGoingLeft() && !status->isPlayerBarrelRolling() && isRollNotCentered) {
            this->currentRollFrame--;
            this->currentFrameRec.x = (float)this->starshipRollTexture.width * 60 - this->currentRollFrame * (float)this->starshipRollTexture.width / 60;
            if (this->currentRollFrame == 0) status->updateMovementFlags(status->isPlayerGoingRight(), false, status->isPlayerGoingUp(), status->isPlayerGoingDown());
        }

        // Background texture window update
        Vector2 currentPosition = status->getCurrentPosition();
        const int starshipSpriteEnd = currentPosition.x + StarshipWidthInPx;
        const int halfWidth = this->getWidth() / 2;
        if (starshipSpriteEnd <= halfWidth) {
            this->currentBackgroundRect.x = 0.0f;
        }
        else if(starshipSpriteEnd > halfWidth && starshipSpriteEnd < BackgroundWidthInPx - halfWidth) {
            this->currentBackgroundRect.x = starshipSpriteEnd - halfWidth;
        }
        else {
            this->currentBackgroundRect.x = BackgroundWidthInPx - this->getWidth();
        }

        this->currentBackgroundRect.y -= (float)BackgroundSpeed;

    }
}

void GameplayScreen::draw(GameStatus *status) {

    ClearBackground(BLACK);
    this->drawBackground();
    this->drawStarship(status);
    this->drawForeground();

}

void GameplayScreen::drawBackground() {
    DrawTextureTiled(this->backgroundTexture, this->currentBackgroundRect, { 0.0f, 0.0f, (float)this->width, (float)this->height }, { 0, 0 }, 0.0f, 1.0f, WHITE);
}

void GameplayScreen::drawStarship(GameStatus *status) {
    if ((status->isPlayerGoingUp() || status->isPlayerGoingDown()) && !status->isPlayerGoingRight() && !status->isPlayerGoingLeft()) {
        DrawTextureRec(this->starshipPitchTexture, this->currentFrameRec, status->getCurrentScreenPosition(), WHITE);
    }
    else {
        DrawTextureRec(this->starshipRollTexture, this->currentFrameRec, status->getCurrentScreenPosition(), WHITE);
    }
}

void GameplayScreen::drawForeground() {

}

GameplayScreen::~GameplayScreen() {
    delete this->inputSequence;
}

void GameplayScreen::updateInputSequence() {
    if (IsKeyDown(KEY_LEFT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_LEFT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_LEFT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_LEFT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_LEFT);
        }
    }

    if (IsKeyDown(KEY_RIGHT)) {
        this->inputSequence->add(InputSequence::KeyStatus::Pressed, KeyboardKey::KEY_RIGHT);
    }
    else if (this->inputSequence->size() != 0) {
        InputSequence::Input lastKeyPressed = this->inputSequence->last();
        if (lastKeyPressed.key == KEY_RIGHT && lastKeyPressed.status == InputSequence::KeyStatus::Pressed && IsKeyUp(KEY_RIGHT)) {
            this->inputSequence->add(InputSequence::KeyStatus::Released, KeyboardKey::KEY_RIGHT);
        }
    }
}
