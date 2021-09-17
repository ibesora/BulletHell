#include "Animations.h"

void Animations::FadeText(const char *text, int posX, int posY, int fontSize, Color color, int currentFrame, int fadeInFramesNumber, int visibleFramesNumber, int fadeOutFramesNumber) {
    float alpha;
    const int fadeOutStartFramesNum = fadeInFramesNumber + visibleFramesNumber;
    if (currentFrame < fadeInFramesNumber) {
        alpha = currentFrame / (float)fadeInFramesNumber;
    }
    else if (currentFrame < fadeOutStartFramesNum) {
        alpha = 1.0;
    }
    else {
        int framesInFadeOut = currentFrame - fadeOutStartFramesNum;
        alpha = (float)1.0 - framesInFadeOut / (float)fadeOutFramesNumber;
    }
    
    DrawText(text, posX, posY, fontSize, Fade(color, alpha));
}

void Animations::MoveText(const char *text, int fontSize, Color color, int startX, int startY, int endX, int endY, int currentFrame, int transitionDurationInFrames) {
    float progress = currentFrame / (float)transitionDurationInFrames;
    int currentX = (int)(startX + (endX - startX) * progress);
    int currentY = (int)(startY + (endY - startY) * progress);

    DrawText(text, currentX, currentY, fontSize, color);
}