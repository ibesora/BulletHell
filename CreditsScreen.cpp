#include "raylib.h"
#include "CreditsScreen.h"

CreditsScreen::CreditsScreen(int width, int height) : Screen(ScreenType::Credits, width, height) {
}

void CreditsScreen::draw() {

    ClearBackground(BLACK);
    DrawText("Credits Screen", 190, 200, 20, LIGHTGRAY);
    DrawText("PROGRAMMING", 190, 220, 20, LIGHTGRAY);
    DrawText("Isaac Besora", 190, 240, 20, LIGHTGRAY);
    DrawText("ASSETS", 190, 330, 20, LIGHTGRAY);
    DrawText("Wobblegut Studios - Starfighter Pack 01", 190, 350, 20, LIGHTGRAY);
    DrawText("Luis Zuno (@anzimuz) - Background and foreground art", 190, 370, 20, LIGHTGRAY);
    DrawText("Loveshadow - TRANSMUTED ( No f{@r ) - ccmixter.org", 190, 390, 20, LIGHTGRAY);
    DrawText("Loveshadow - Stay Calm - ccmixter.org", 190, 410, 20, LIGHTGRAY);
    DrawText("Sci-Fi Sounds - Kenney.nl", 190, 430, 20, LIGHTGRAY);

}