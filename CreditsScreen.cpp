#include "raylib.h"
#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void CreditsScreen::draw(GameStatus *current) {

    ClearBackground(RAYWHITE);
    DrawText("Credits Screen", 190, 200, 20, LIGHTGRAY);
    DrawText("ASSETS", 190, 330, 20, LIGHTGRAY);
    DrawText("Wobblegut Studios - Starfighter Pack 01", 190, 350, 20, LIGHTGRAY);
    DrawText("Luis Zuno (@anzimuz) - Background and foreground art", 190, 370, 20, LIGHTGRAY);

}