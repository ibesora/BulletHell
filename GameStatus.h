#pragma once

class Screen;

class GameStatus {
public:
    GameStatus(Screen *initialScreen);
    Screen *getCurrentScreen();
    void update();
    void changeCurrentScreen(Screen *nextScreen);
    ~GameStatus();

protected:
    Screen *currentScreen;
};