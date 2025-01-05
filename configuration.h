#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <TFT_eSPI.h>
#include <Keypad.h>
#include <EEPROM.h>

void configurazione(TFT_eSPI &tft, Keypad &keypad, int &countdownTime, String &disinnescoCode);
void modificaCountdown(TFT_eSPI &tft, Keypad &keypad, int &countdownTime);
void modificaCodice(TFT_eSPI &tft, Keypad &keypad, String &disinnescoCode);

#endif