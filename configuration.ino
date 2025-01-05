#include "configuration.h"
#include <TFT_eSPI.h>
#include <Keypad.h>
#include <EEPROM.h>

const int potPin = A0; // Dichiarazione di potPin

void configurazione(TFT_eSPI &tft, Keypad &keypad, int &countdownTime, String &disinnescoCode)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.println("Configurazione");

    tft.fillRect(0, 40, tft.width(), 60, TFT_DARKGREY);
    tft.drawRect(0, 40, tft.width(), 60, TFT_WHITE);
    tft.fillRect(0, 100, tft.width(), 60, TFT_DARKGREY);
    tft.drawRect(0, 100, tft.width(), 60, TFT_WHITE);
    tft.fillRect(0, 160, tft.width(), 60, TFT_DARKGREY);
    tft.drawRect(0, 160, tft.width(), 60, TFT_WHITE);

    tft.setTextColor(TFT_YELLOW, TFT_DARKGREY);
    tft.setTextSize(2);
    tft.setCursor(10, 50);
    tft.println("A. Modifica Countdown");

    tft.setTextColor(TFT_GREEN, TFT_DARKGREY);
    tft.setCursor(10, 110);
    tft.println("B. Modifica Codice");

    tft.setTextColor(TFT_RED, TFT_DARKGREY);
    tft.setCursor(10, 170);
    tft.println("#. Torna al Menu Principale");

    while (true)
    {
        char key = keypad.getKey();
        if (key)
        {
            if (key == 'A')
            {
                modificaCountdown(tft, keypad, countdownTime);
                break;
            }
            else if (key == 'B')
            {
                modificaCodice(tft, keypad, disinnescoCode);
                break;
            }
            else if (key == '#')
            {
                showGameMenu(tft);
                break;
            }
        }
    }
}

void modificaCountdown(TFT_eSPI &tft, Keypad &keypad, int &countdownTime)
{
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.println("Modifica Tempo Countdown");

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 60);
    tft.print("Tempo attuale: ");
    tft.print(countdownTime);
    tft.println(" minuti");

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 100);
    tft.println("Nuovo tempo:");

    // Mostra i messaggi di conferma e ritorno indietro
    tft.setCursor(0, 230);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println("Premi # per confermare");
    tft.setCursor(0, 260);
    tft.println("Premi * per tornare indietro");

    int lastMinutes = -1;

    while (true)
    {
        int potValue = analogRead(potPin);
        int minutes = map(potValue, 0, 1023, 0, 240);

        static int averageMinutes = minutes;
        averageMinutes = (averageMinutes * 3 + minutes) / 4;

        if (averageMinutes != lastMinutes)
        {
            tft.fillRect(0, 160, tft.width(), 30, TFT_BLACK);
            tft.setCursor(0, 160);
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.setTextSize(3);
            tft.print(averageMinutes);
            tft.println(" minuti");

            int barWidth = map(averageMinutes, 0, 240, 0, tft.width());
            tft.fillRect(0, 200, tft.width(), 20, TFT_BLACK);
            tft.fillRect(0, 200, barWidth, 20, TFT_GREEN);

            lastMinutes = averageMinutes;
        }

        char key = keypad.getKey();
        if (key)
        {
            if (key == '#')
            {
                countdownTime = averageMinutes;
                EEPROM.write(countdownAddress, countdownTime);
                tft.fillScreen(TFT_BLACK);
                tft.setCursor(0, 0);
                tft.setTextSize(3);
                tft.setTextColor(TFT_GREEN, TFT_BLACK);
                tft.println("Tempo salvato!");
                delay(2000);
                configurazione(tft, keypad, countdownTime, disinnescoCode);
                break;
            }
            else if (key == '*')
            {
                configurazione(tft, keypad, countdownTime, disinnescoCode);
                break;
            }
        }

        delay(100);
    }
}

void modificaCodice(TFT_eSPI &tft, Keypad &keypad, String &disinnescoCode)
{
    String nuovoCodice = "";
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.println("Modifica Codice");

    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 60);
    tft.print("Codice attuale: ");
    tft.print(disinnescoCode);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 100);
    tft.println("Nuovo codice:");

    // Mostra i messaggi di conferma e ritorno indietro
    tft.setCursor(0, 230);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.println("Premi # per confermare");
    tft.setCursor(0, 260);
    tft.println("Premi * per tornare indietro");

    while (true)
    {
        char key = keypad.getKey();
        if (key)
        {
            if (key == '#')
            {
                if (nuovoCodice.length() > 0)
                {
                    disinnescoCode = nuovoCodice;
                    EEPROM.put(codeAddress, disinnescoCode);
                    tft.fillScreen(TFT_BLACK);
                    tft.setCursor(0, 0);
                    tft.setTextSize(3);
                    tft.setTextColor(TFT_GREEN, TFT_BLACK);
                    tft.println("Codice salvato!");
                    delay(2000);
                    configurazione(tft, keypad, countdownTime, disinnescoCode);
                    break;
                }
                else
                {
                    tft.setTextColor(TFT_RED, TFT_BLACK);
                    tft.println("Codice non valido! Deve essere non vuoto.");
                    delay(2000);
                    tft.fillRect(0, 60, tft.width(), tft.height() - 60, TFT_BLACK);
                    tft.setCursor(0, 60);
                    tft.setTextColor(TFT_YELLOW, TFT_BLACK);
                    tft.setTextSize(2);
                    tft.print("Codice attuale: ");
                    tft.print(disinnescoCode);

                    tft.setTextColor(TFT_GREEN, TFT_BLACK);
                    tft.setTextSize(3);
                    tft.setCursor(0, 100);
                    tft.println("Nuovo codice:");
                    nuovoCodice = "";
                }
            }
            else if (key == '*')
            {
                configurazione(tft, keypad, countdownTime, disinnescoCode);
                break;
            }
            else
            {
                nuovoCodice += key;
                tft.fillRect(0, 140, tft.width(), 30, TFT_BLACK); // Cancella l'area sotto "Nuovo codice" prima di stampare il nuovo codice
                tft.setCursor(0, 140);
                tft.print(nuovoCodice);
            }
        }
    }
}