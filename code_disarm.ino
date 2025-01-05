#include "code_disarm.h"

void disinnescoCodice(TFT_eSPI &tft, Keypad &keypad, String &disinnescoCode)
{
    String inputCode = "";
    tft.fillScreen(TFT_BLACK);

    tft.setTextColor(TFT_CYAN, TFT_BLACK);
    tft.setTextSize(3);
    tft.setCursor(0, 0);
    tft.println("Disinnesco Codice");

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 60);
    tft.print("Inserisci il codice:");

    while (true)
    {
        char key = keypad.getKey();
        if (key)
        {
            if (key == '#')
            {
                if (inputCode == disinnescoCode)
                {
                    tft.fillScreen(TFT_BLACK);
                    tft.setTextColor(TFT_GREEN, TFT_BLACK);
                    tft.setTextSize(3);
                    tft.setCursor(0, 0);
                    tft.println("Codice corretto! Bomba disinnescata.");
                }
                else
                {
                    tft.fillScreen(TFT_BLACK);
                    tft.setTextColor(TFT_RED, TFT_BLACK);
                    tft.setTextSize(3);
                    tft.setCursor(0, 0);
                    tft.println("Codice errato! Bomba esplosa.");
                }
                delay(2000);
                showGameMenu(tft);
                break;
            }
            else if (key == '*')
            {
                showGameMenu(tft);
                break;
            }
            else
            {
                if (inputCode.length() < 4)
                {
                    inputCode += key;
                    tft.fillRect(0, 80, tft.width(), 30, TFT_BLACK); // Cancella l'area sotto "Inserisci il codice" prima di stampare il codice inserito
                    tft.setCursor(0, 80);
                    tft.print(inputCode);
                }
            }
        }
    }
}