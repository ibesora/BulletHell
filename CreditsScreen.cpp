#include "raylib.h"
#include "CreditsScreen.h"
#include "Texts.h"
#include "InputHandler.h"
#include "GameStatus.h"
#include "TitleScreen.h"
#include "TextRenderer.h"

CreditsScreen::CreditsScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void CreditsScreen::updateGameStatus() {
    if (InputHandler::getInstance().isKeyPressed(KEY_ENTER)) {
        GameStatus::getInstance().changeCurrentScreen(new TitleScreen(this->width, this->height, false));
    }
}

void CreditsScreen::draw() {

    ClearBackground(BLACK);
    TextRenderer::getInstance().draw(Texts::Programming, 190, 220, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::MyName, 190, 240, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::Assets, 190, 330, 20, YELLOW);
    TextRenderer::getInstance().draw(Texts::StarfighterPackCredits, 190, 350, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::BackgroundCredits, 190, 370, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::GameMusicCredits, 190, 390, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::MenuMusicCredits, 190, 410, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::SoundFXCredits, 190, 430, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::FontCredits, 190, 450, 20, LIGHTGRAY);
    TextRenderer::getInstance().draw(Texts::GoBackToTitleScreen, 190, 500, 20, YELLOW);

}