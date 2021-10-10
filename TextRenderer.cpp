#include "TextRenderer.h"
#include "AssetStore.h"


TextRenderer::TextRenderer() {
}

TextRenderer &TextRenderer::getInstance() {
    static TextRenderer instance;
    return instance;
}

void TextRenderer::draw(const char *text, int posX, int posY, int fontSize, Color color) {
    DrawTextEx(AssetStore::getInstance().getCustomFont(), text, { (float)posX, (float)posY }, fontSize, 0, color);
}