#ifndef WIRE_DISARM_H
#define WIRE_DISARM_H

#include <TFT_eSPI.h>
#include <Keypad.h>

void disinnescoFili(TFT_eSPI &tft, Keypad &keypad);
void handleWireCut(TFT_eSPI &tft, int wirePin, int correctWirePin);

#endif