#pragma once
#include "raylib.h"

class Animations {
public:
    // Shows text with the given font size and in the desired position. The text fades in during fadeInFramesNumber frames, stays visible during visibleFrameNumber frames
    // and then fades out during fadeOutFrameNumber
    static void FadeText(const char *text, int posX, int posY, int fontSize, Color color, int currentFrame, int fadeInFramesNumber, int visibleFrameNumber, int fadeOutFrameNumber);
    static void MoveText(const char *text, int fontSize, Color color, int startX, int startY, int endX, int endY, int currentFrame, int transitionDurationInFrames);
};