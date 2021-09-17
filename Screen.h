#pragma once
enum class ScreenType { Logo, Title, Pause, Gameplay, Ending };

class GameStatus;

class Screen {
public:
    Screen(ScreenType type) {
        this->type = type;
    };

    virtual void updateGameStatus(GameStatus *) {};
    virtual void draw() = 0;

protected:
    ScreenType type;
};