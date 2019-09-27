#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"
#include <Wire.h>
#include "ttgo_display_pindef.h"

TFT_eSPI tft = TFT_eSPI(135, 240); // instance "tft" de la classe TFT_eSPI (largeur, hauteur)

unsigned long milliprec;
char buff[512];

void setup()
{
    Serial.begin(115200);
    delay(1000);

    Serial.println("Start");
    tft.init();
    tft.setRotation(1); // texte affiche sur la plus grande longueur
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);
    tft.setTextDatum(MC_DATUM);

    if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
            }

    tft.drawString("Debut", tft.width() / 2, tft.height() / 2);
    delay(2000);
    milliprec = millis();

}


void loop()
{
        if ( (millis()-milliprec)>2000) {
            tft.fillScreen(TFT_BLACK);
            tft.setTextDatum(MC_DATUM);
//            tft.setTextColor(TFT_WHITE, TFT_BLACK);
//            tft.setTextSize(2);
//            tft.setRotation(1); // texte affiche sur la plus grande longueur
            tft.drawString("Blink",  tft.width() / 2, tft.height() / 2 );
            milliprec = millis();
          
            delay(1000);
            tft.fillScreen(TFT_BLACK);
            }
        
}
