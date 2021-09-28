#pragma once
enum class ScreenType { Logo, Title, Pause, Gameplay, Ending, Credits };

class GameStatus;

class Screen {
public:
    Screen(ScreenType type, int width, int height) {
        this->type = type;
        this->width = width;
        this->height = height;
    };

    ScreenType getType() { return this->type; }
    int getWidth() { return this->width; }
    int getHeight() { return this->height; }

    virtual void updateGameStatus(GameStatus *) {};
    virtual void draw(GameStatus*) = 0;

protected:
    ScreenType type;
    int width;
    int height;
};