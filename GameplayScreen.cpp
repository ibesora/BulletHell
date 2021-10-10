#include <cstdlib>
#include "raylib.h"
#include "Player.h"
#include "GameplayScreen.h"
#include "PauseScreen.h"
#include "GameStatus.h"
#include "InputHandler.h"
#include "AssetStore.h"
#include "PowerUp.h"
#include "Animations.h"
#include "Texts.h"

const int StarshipWidthInPx = 256;
const int BackgroundWidthInPx = 1920;
const int BulletRadius = 10;
const int FadeInFramesNum = 60;
const int VisibleFramesNum = 60;
const int FadeOutFramesNum = 60;
const int TotalTextAnimationFrames = FadeInFramesNum + VisibleFramesNum + FadeOutFramesNum;

GameplayScreen::GameplayScreen(int width, int height) : Screen(ScreenType::Gameplay, width, height) {
    this->currentFrameRec = { 0.0f, 0.0f, (float)AssetStore::getInstance().getStarshipRollTexture().width / 60, (float)AssetStore::getInstance().getStarshipRollTexture().height };
    this->currentBackgroundRect = { 0.0f, 0.0f, (float)width, (float)height };
    this->textAnimFrame = 0;
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
    this->drawPowerUps();
    this->drawStarship();
    this->drawBullets();
    this->drawEnemyBullets();
    this->drawForeground();
    this->drawEnemyLife();
    this->drawPlayerLife();
    this->drawText();

}

void GameplayScreen::drawBackground() {
    DrawTextureTiled(AssetStore::getInstance().getBackgroundTexture(), this->currentBackgroundRect, { 0.0f, 0.0f, (float)this->width, (float)this->height }, { 0, 0 }, 0.0f, 1.0f, WHITE);
}

void GameplayScreen::drawStarship() {
    Player *player = GameStatus::getInstance().getPlayer();
    Color col = GameStatus::getInstance().isPlayerBeingHit() ? RED : WHITE;
    if ((player->isGoingUp() || player->isGoingDown()) && !player->isGoingRight() && !player->isGoingLeft()) {
        DrawTextureRec(AssetStore::getInstance().getStarshipPitchTexture(), this->currentFrameRec, GameStatus::getInstance().getPlayerScreenPosition(), col);
    }
    else {
        DrawTextureRec(AssetStore::getInstance().getStarshipRollTexture(), this->currentFrameRec, GameStatus::getInstance().getPlayerScreenPosition(), col);
    }
}

void GameplayScreen::drawPowerUps() {
    for (int i = 0; i < GameStatus::getInstance().getPowerUpsNumber(); ++i) {
        PowerUp current = GameStatus::getInstance().getPowerUp(i);
        const Rectangle rect = { current.isLighted() ? 64.0f : 0.0f, 0.0f, 64.0f, 64.0f };
        Vector2 position = { current.getPosition().x - GameStatus::getInstance().getBackgroundPosition().x, current.getPosition().y };
        DrawTextureRec(AssetStore::getInstance().getPowerUpTexture(), rect, position, WHITE);
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
        DrawCircleGradient((int)bullet.position.x - (int)GameStatus::getInstance().getBackgroundPosition().x, (int)bullet.position.y, BulletRadius, YELLOW, RED);
    }
}

void GameplayScreen::drawEnemies() {
    const Rectangle rect = { 0.0f, 0.0f, (float)AssetStore::getInstance().getMainEnemyTexture().width, (float)AssetStore::getInstance().getMainEnemyTexture().height };
    const Vector2 absoluteEnemyPosition = GameStatus::getInstance().getEnemyPosition();
    Vector2 position = { absoluteEnemyPosition.x - GameStatus::getInstance().getBackgroundPosition().x, absoluteEnemyPosition.y};
    if (GameStatus::getInstance().hasEnemyAppeared()) {
        DrawTextureRec(AssetStore::getInstance().getMainEnemyTexture(), rect, position, GameStatus::getInstance().isEnemyBeingHit() ? RED : WHITE);
    }
    else {
        DrawTextureRec(AssetStore::getInstance().getMainEnemyTexture(), rect, position, Fade(WHITE, GameStatus::getInstance().getEnemyAppearingAnimationProgress()));
    }
}

void GameplayScreen::drawEnemyBullets() {
    for (int i = 0; i < GameStatus::getInstance().getEnemyBulletsNumber(); ++i) {
        GameStatus::BulletInfo bullet = GameStatus::getInstance().getEnemyBullet(i);
        DrawCircleGradient((int)bullet.position.x - (int)GameStatus::getInstance().getBackgroundPosition().x, (int)bullet.position.y, BulletRadius, BLUE, YELLOW);
    }
}

void GameplayScreen::drawEnemyLife() {
    if (GameStatus::getInstance().hasEnemyAppeared()) {
        const Vector2 absoluteEnemyPosition = GameStatus::getInstance().getEnemyPosition();
        const int enemyLife = GameStatus::getInstance().getEnemyLife();
        const float greenLifeBarX = absoluteEnemyPosition.x - GameStatus::getInstance().getBackgroundPosition().x + StarshipWidthInPx / 2 - 50.0f;
        const int lifeInPx = enemyLife / 10;
        const float redLifeBarX = greenLifeBarX + lifeInPx;
        const float lifeBarY = absoluteEnemyPosition.y + StarshipWidthInPx / 2 - 20.0f;
        Vector2 positionGreen = { greenLifeBarX, lifeBarY };
        Vector2 positionRed = { redLifeBarX, lifeBarY };
        DrawRectangleV(positionGreen, { (float)lifeInPx, 20.0f }, GREEN);
        DrawRectangleV(positionRed, { (float)100.0f - lifeInPx, 20.0f }, RED);
    }
}

void GameplayScreen::drawPlayerLife() {
    if (!GameStatus::getInstance().hasEnemyAppeared()) return;
    const Vector2 position = GameStatus::getInstance().getPlayerScreenPosition();
    const int playerLife = GameStatus::getInstance().getPlayerLife();
    const float greenLifeBarX = position.x + StarshipWidthInPx / 2 - 50.0f;
    const int lifeInPx = playerLife / 10;
    const float redLifeBarX = greenLifeBarX + lifeInPx;
    const float lifeBarY = position.y + StarshipWidthInPx / 2 + 50.0f;
    Vector2 positionGreen = { greenLifeBarX, lifeBarY };
    Vector2 positionRed = { redLifeBarX, lifeBarY };
    DrawRectangleV(positionGreen, { (float)lifeInPx, 20.0f }, GREEN);
    DrawRectangleV(positionRed, { (float)100.0f - lifeInPx, 20.0f }, RED);
}

void GameplayScreen::drawText() {
    if (!GameStatus::getInstance().hasEnemyAppeared()) {
        this->textAnimFrame++;
        Animations::FadeText(Texts::EnemyIncomingText, 150, this->height / 2 - 50, 100, RED, this->textAnimFrame, FadeInFramesNum, VisibleFramesNum, FadeOutFramesNum);
        if (this->textAnimFrame == TotalTextAnimationFrames) this->textAnimFrame = 0;
    }
}
