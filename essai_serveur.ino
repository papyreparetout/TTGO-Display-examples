#include <WiFi.h>
  #include <TFT_eSPI.h>
  #include <SPI.h>
  #include <Wire.h>
  #include "ttgo_display_pindef.h"

  TFT_eSPI tft = TFT_eSPI(135, 240); // instance "tft" de la classe TFT_eSPI (largeur, hauteur)
  
const char* ssid     = "Livebox-08B6";
const char* password = "jrfeajroguin1978";
/* create a server and listen on port 8088 */
WiFiServer server(8088);
void setup()
{
    Serial.begin(115200);
    // demarrage ecran tft
          tft.init();
    tft.setRotation(1); // texte affiche sur la plus grande longueur
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.setCursor(0, 0);
    if (TFT_BL > 0) {
        pinMode(TFT_BL, OUTPUT);
        digitalWrite(TFT_BL, HIGH);
            }
  
    tft.drawString("Debut", 0, 0);
    delay(1000);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.setTextDatum(TL_DATUM);
    tft.setCursor(0, 0);
    
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* connecting to WiFi */
    WiFi.begin(ssid, password);
    /*wait until ESP32 connect to WiFi*/
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        tft.print(".");
    }
    tft.println("");
    tft.print("IP : ");
    tft.println(WiFi.localIP());
    /* start Server */
    server.begin();
    delay(1000);
     tft.setRotation(1);
     tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setTextDatum(MC_DATUM);
    tft.setCursor(0, 0);
}
void loop(){
   
    /* listen for client */
    WiFiClient client = server.available(); 
    uint8_t data[30]; 
    if (client) {                   
      Serial.println("new client");         
      /* check client is connected */           
      while (client.connected()) {          
          if (client.available()) {
              int len = client.read(data, 30);
              if(len < 30){
                  data[len] = '\0';  
              }else {
                  data[29] = '\0';
              }    
              Serial.print("client sent: ");
              tft.fillScreen(TFT_BLACK);
              tft.setTextDatum(MC_DATUM);
              tft.setCursor(0, 0);            
              tft.println((char *)data); 
          }
      } 
    }
}
