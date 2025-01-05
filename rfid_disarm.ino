#include "rfid_disarm.h"

// Pin del modulo RFID
#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Crea un'istanza del modulo MFRC522

void setupRFID()
{
    SPI.begin();        // Inizializza SPI bus
    mfrc522.PCD_Init(); // Inizializza MFRC522
}

void disinnescoRFID(TFT_eSPI &tft)
{
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextSize(2);
    tft.setCursor(0, 0);
    tft.println("Disinnesco RFID");
    tft.println("Avvicina la chiave:");

    setupRFID();

    while (true)
    {
        // Vedi se c'è una nuova carta presente
        if (!mfrc522.PICC_IsNewCardPresent())
        {
            continue;
        }

        // Se c'è una carta disponibile, leggi la carta
        if (!mfrc522.PICC_ReadCardSerial())
        {
            continue;
        }

        // Mostra UID della carta
        String uid = "";
        for (byte i = 0; i < mfrc522.uid.size; i++)
        {
            uid += String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "");
            uid += String(mfrc522.uid.uidByte[i], HEX);
        }
        uid.toUpperCase();

        // UID corretto della chiave RFID
        String correctUID = "AABBCCDD"; // Sostituisci con il UID corretto

        if (uid == correctUID)
        {
            tft.setTextColor(TFT_GREEN, TFT_BLACK);
            tft.println("Chiave corretta! Bomba disinnescata.");
        }
        else
        {
            tft.setTextColor(TFT_RED, TFT_BLACK);
            tft.println("Chiave errata! Bomba esplosa.");
        }
        delay(2000);
        showGameMenu(tft);
        break;
    }
}