#include <cstdlib>
#include "raylib.h"
#include "Player.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputHandler.h"
#include "AssetStore.h"

const int StarshipWidthInPx = 256;
const int BackgroundWidthInPx = 1920;
const int BulletRadius = 10;

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

    Player *player = GameStatus::getInstance().getPlayer();
    bool isRollNotCentered = player->getCurrentRollFrame() != 0;
    bool isPitchNotCentered = player->getCurrentPitchFrame() != 0;
    const Texture2D starshipPitchTexture = AssetStore::getInstance().getStarshipPitchTexture();
    const Texture2D starshipRollTexture = AssetStore::getInstance().getStarshipRollTexture();

    // User is pressing up or pitch animation up is running
    if (InputHandler::getInstance().isKeyDown(KEY_UP)
        || (InputHandler::getInstance().isKeyUp(KEY_UP) && player->isGoingUp() && isPitchNotCentered)) {
        this->currentFrameRec.x = (float)starshipPitchTexture.width * 60 - player->getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }

    // User is pressing down or pitch animation down is running
    if (InputHandler::getInstance().isKeyDown(KEY_DOWN)
        || (InputHandler::getInstance().isKeyUp(KEY_DOWN) && player->isGoingDown() && isPitchNotCentered)) {
        this->currentFrameRec.x = player->getCurrentPitchFrame() * (float)starshipPitchTexture.width / 60;
    }

    // User is pressing right, roll animation right is running or right barrel roll animation is running
    if (player->isBarrelRollingRight()
        || (InputHandler::getInstance().isKeyDown(KEY_RIGHT))
        || (InputHandler::getInstance().isKeyUp(KEY_RIGHT) && player->isGoingRight() && !player->isBarrelRolling() && isRollNotCentered)) {
        this->currentFrameRec.x = player->getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }

    // User is pressing left, roll animation left is running or left barrel roll animation is running
    if (player->isBarrelRollingLeft()
        || (InputHandler::getInstance().isKeyDown(KEY_LEFT))
        || (InputHandler::getInstance().isKeyUp(KEY_LEFT) && player->isGoingLeft() && !player->isBarrelRolling() && isRollNotCentered)) {
        this->currentFrameRec.x = (float)starshipRollTexture.width * 60 - player->getCurrentRollFrame() * (float)starshipRollTexture.width / 60;
    }
}

void GameplayScreen::updateBackgroundTexture() {
    this->currentBackgroundRect.x = GameStatus::getInstance().getBackgroundPosition().x;
    this->currentBackgroundRect.y = GameStatus::getInstance().getBackgroundPosition().y;
}

void GameplayScreen::draw() {

    ClearBackground(BLACK);
    this->drawBackground();
    this->drawEnemies();
    this->drawStarship();
    this->drawBullets();
    this->drawEnemyBullets();
    this->drawForeground();

}

void GameplayScreen::drawBackground() {
    DrawTextureTiled(AssetStore::getInstance().getBackgroundTexture(), this->currentBackgroundRect, { 0.0f, 0.0f, (float)this->width, (float)this->height }, { 0, 0 }, 0.0f, 1.0f, WHITE);
}

void GameplayScreen::drawStarship() {
    Player *player = GameStatus::getInstance().getPlayer();
    if ((player->isGoingUp() || player->isGoingDown()) && !player->isGoingRight() && !player->isGoingLeft()) {
        DrawTextureRec(AssetStore::getInstance().getStarshipPitchTexture(), this->currentFrameRec, GameStatus::getInstance().getPlayerScreenPosition(), WHITE);
    }
    else {
        DrawTextureRec(AssetStore::getInstance().getStarshipRollTexture(), this->currentFrameRec, GameStatus::getInstance().getPlayerScreenPosition(), WHITE);
    }
}

void GameplayScreen::drawForeground() {

    const Rectangle rect = { this->currentBackgroundRect.x, 0.0f, (float)this->width, (float)AssetStore::getInstance().getForegroundTexture().height };
    for (int i = 0; i < GameStatus::getInstance().getCloudsNumber(); ++i) {
        DrawTextureRec(AssetStore::getInstance().getForegroundTexture(), rect, { 0.0f, (float)GameStatus::getInstance().getCloudYPosition(i) }, WHITE);
    }

}

void GameplayScreen::drawBullets() {
    for (int i = 0; i < GameStatus::getInstance().getBulletsNumber(); ++i) {
        GameStatus::BulletInfo bullet = GameStatus::getInstance().getBullet(i);
        DrawCircleGradient((int)bullet.position.x - GameStatus::getInstance().getBackgroundPosition().x, (int)bullet.position.y, BulletRadius, YELLOW, RED);
    }
}

void GameplayScreen::drawEnemies() {
    const Rectangle rect = { 0.0f, 0.0f, (float)AssetStore::getInstance().getMainEnemyTexture().width, (float)AssetStore::getInstance().getMainEnemyTexture().height };
    const Vector2 absoluteEnemyPosition = GameStatus::getInstance().getEnemyPosition();
    Vector2 position = { absoluteEnemyPosition.x - GameStatus::getInstance().getBackgroundPosition().x, absoluteEnemyPosition.y};
    DrawTextureRec(AssetStore::getInstance().getMainEnemyTexture(), rect, position, GameStatus::getInstance().isEnemyBeingHit() ? RED : WHITE);
}

void GameplayScreen::drawEnemyBullets() {
    for (int i = 0; i < GameStatus::getInstance().getEnemyBulletsNumber(); ++i) {
        GameStatus::BulletInfo bullet = GameStatus::getInstance().getEnemyBullet(i);
        DrawCircleGradient((int)bullet.position.x - GameStatus::getInstance().getBackgroundPosition().x, (int)bullet.position.y, BulletRadius, BLUE, YELLOW);
    }

}
