#include <TFT_eSPI.h>
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Keypad.h>
#include <EEPROM.h>
#include <MFRC522.h>

#include "welcome_screen.h"
#include "game_menu.h"
#include "wire_disarm.h"
#include "code_disarm.h"
#include "configuration.h"
#include "rfid_disarm.h"

TFT_eSPI tft = TFT_eSPI();
RTC_DS3231 rtc;

// Configurazione del tastierino
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {30, 31, 32, 33};
byte colPins[COLS] = {34, 35, 36, 37};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool isOnWelcomeScreen = true;

// Indirizzo EEPROM per memorizzare il tempo del countdown e il codice
const int countdownAddress = 0;
const int codeAddress = 10;
int countdownTime = 0;
String disinnescoCode = "1234";

void setup()
{
    Serial.begin(9600);
    tft.init();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        while (1);
    }
    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, setting the time!");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    countdownTime = EEPROM.read(countdownAddress);
    char savedCode[21]; // Modifica la dimensione dell'array in base alla lunghezza massima del codice
    EEPROM.get(codeAddress, savedCode);
    disinnescoCode = String(savedCode);

    showWelcomeScreen(tft);
}

void loop()
{
    char key = keypad.getKey();
    if (key)
    {
        Serial.println(key);
        handleKeypadInput(key);
    }
}

void handleKeypadInput(char key)
{
    if (key == '#')
    {
        if (isOnWelcomeScreen)
        {
            isOnWelcomeScreen = false;
            showGameMenu(tft);
        }
    }
    else if (!isOnWelcomeScreen)
    {
        switch (key)
        {
        case '1':
            configurazione(tft, keypad, countdownTime, disinnescoCode);
            break;
        case '2':
            disinnescoFili(tft, keypad);
            break;
        case '3':
            disinnescoCodice(tft, keypad, disinnescoCode);
            break;
        case '4':
            disinnescoRFID(tft);
            break;
        default:
            break;
        }
    }
}