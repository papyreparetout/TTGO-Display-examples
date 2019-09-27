/*
 * There are three serial ports on the ESP known as U0UXD, U1UXD and U2UXD.
 * 
 * U0UXD is used to communicate with the ESP32 for programming and during reset/boot.
 * U1UXD is unused and can be used for your projects. Some boards use this port for SPI Flash access though
 * U2UXD is unused and can be used for your projects.
 * 
*/
#include <TFT_eSPI.h>
#include <SPI.h>
#include "WiFi.h"
#include <Wire.h>
#include "ttgo_display_pindef.h"

TFT_eSPI tft = TFT_eSPI(135, 240); // instance "tft" de la classe TFT_eSPI (largeur, hauteur)

#define RXD2 37
#define TXD2 38
 
void setup() {
  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  //Serial1.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  Serial.println("Serial Txd is on pin: "+String(TXD2));
  Serial.println("Serial Rxd is on pin: "+String(RXD2));
  tft.init();
    tft.setRotation(0); // texte affiche sur la plus petite dimension
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(TL_DATUM);
    tft.setCursor(0, 0);
    if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
            }
  
    tft.drawString("Debut", 0, 0);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
}
 
void loop() { //Choose Serial1 or Serial2 as required
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
    tft.setCursor(0, 0);
  while (Serial2.available()) {
    char recu = Serial2.read();
    Serial.print(recu);
    tft.print (recu);
  }
}
