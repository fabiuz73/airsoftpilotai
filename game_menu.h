#ifndef GAME_MENU_H
#define GAME_MENU_H

#include <TFT_eSPI.h>

void showGameMenu(TFT_eSPI &tft);
void drawButton(TFT_eSPI &tft, int x, int y, int w, int h, uint16_t color, const char* label);

#endif