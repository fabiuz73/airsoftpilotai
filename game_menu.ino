#include "game_menu.h"

void showGameMenu(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);

    int buttonHeight = tft.height() / 4; // Modificato il numero di opzioni
    drawButton(tft, 0, 0, tft.width(), buttonHeight, TFT_RED, "1. Configurazione");
    drawButton(tft, 0, buttonHeight, tft.width(), buttonHeight, TFT_GREEN, "2. Disinnesco Fili");
    drawButton(tft, 0, 2 * buttonHeight, tft.width(), buttonHeight, TFT_BLUE, "3. Disinnesco Codice");
    drawButton(tft, 0, 3 * buttonHeight, tft.width(), buttonHeight, TFT_ORANGE, "4. Disinnesco RFID");
}

void drawButton(TFT_eSPI &tft, int x, int y, int w, int h, uint16_t color, const char* label)
{
    tft.fillRect(x, y, w, h, color);
    tft.drawRect(x, y, w, h, TFT_WHITE);
    tft.drawRect(x + 2, y + 2, w - 4, h - 4, TFT_WHITE);
    tft.setTextColor(TFT_BLACK, color);
    tft.setTextSize(3);
    uint16_t textWidth = tft.textWidth(label);
    tft.setCursor(x + (w - textWidth) / 2, y + (h / 2) - 12);
    tft.println(label);
}