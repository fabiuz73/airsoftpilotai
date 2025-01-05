#include "wire_disarm.h"

void disinnescoFili(TFT_eSPI &tft, Keypad &keypad)
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Disinnesco Fili");

    // Implementare la logica di disinnesco fili qui
}

void handleWireCut(TFT_eSPI &tft, int wirePin, int correctWirePin)
{
    // Implementare la logica per gestire il taglio del filo qui
}