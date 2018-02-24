#include "DHT.h"
//#include <ESP8266WiFi.h>
//#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306.h" // alias for `#include "SSD1306Wire.h"`
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SSD1306  display(0x3c, 4, 5);

void setup()
{
  Serial.begin(115200);
  Serial.println("Init setup");
  
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.flipScreenVertically();
  display.drawString(5, 10, "Internet of Things");
  display.drawString(40, 30, "IoT A/C");
  display.display();
  delay(5000);

  dht.begin();
}

void loop()
{
  display.clear();
  delay(3000); // greater than 3s to stable 
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.println(temp);
  Serial.println(humi);
  
  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  display.drawString(5, 10, "TEMP:" + String(temp, 2) + " Deg");
  Serial.println("TEMP:" + String(temp, 2));
  display.drawString(5, 40, "HUMI:" + String(humi, 2) + " %");
  Serial.println("HUMI:" + String(humi, 2));
  display.display();
Ư