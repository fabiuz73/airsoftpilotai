#ifndef CODE_DISARM_H
#define CODE_DISARM_H

#include <TFT_eSPI.h>
#include <Keypad.h>

void disinnescoCodice(TFT_eSPI &tft, Keypad &keypad, String &disinnescoCode);

#endif