#include "welcome_screen.h"

void showWelcomeScreen(TFT_eSPI &tft)
{
    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);

    int16_t xpos, ypos;
    uint16_t w = tft.textWidth("AirsoftCopilot AI Scenography");
    xpos = (tft.width() - w) / 2;
    ypos = 20;

    tft.setCursor(xpos, ypos);
    tft.println("AirsoftCopilot AI Scenography");

    drawAngryFace(tft);

    tft.setTextColor(TFT_RED, TFT_BLACK);
    w = tft.textWidth("PREMERE TASTO #");
    xpos = (tft.width() - w) / 2;
    ypos = tft.height() - 30;

    tft.setCursor(xpos, ypos);
    tft.println("PREMERE TASTO #");
}

void drawAngryFace(TFT_eSPI &tft)
{
    tft.fillCircle(240, 160, 100, TFT_YELLOW);
    tft.drawCircle(240, 160, 100, TFT_BLACK);
    tft.fillCircle(200, 140, 10, TFT_BLACK);
    tft.fillCircle(280, 140, 10, TFT_BLACK);
    tft.drawLine(180, 110, 220, 140, TFT_BLACK);
    tft.drawLine(260, 140, 300, 110, TFT_BLACK);
    tft.drawLine(200, 190, 240, 220, TFT_BLACK);
    tft.drawLine(240, 220, 280, 190, TFT_BLACK);
}