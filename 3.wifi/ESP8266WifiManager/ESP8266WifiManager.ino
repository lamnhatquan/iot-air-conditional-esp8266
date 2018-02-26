#include "DHT.h"
#include <ESP8266WiFi.h>
#include "SSD1306.h"
#include "WiFiManager.h"

#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
SSD1306  display(0x3c, 4, 5);

void setupWifi()
{
  WiFiManager wifiManager;
  Serial.println("Wifi Manager");
  Serial.println("IP: 192.168.4.1");

  display.clear();
  display.drawString(10, 10, "Wifi Manager");
  display.drawString(0, 30, "Access-your-network");
  display.display();
  delay(3000);
  if (!wifiManager.autoConnect("your-name-network")) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  }
  display.clear();
  display.drawString(20, 20, "Connected");
  display.display();
  Serial.println("connected...yeey :)");
}
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


  setupWifi();
  dht.begin();
}

void loop()
{
  display.clear();
  delay(2000); // greater than 3s to stable
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.println(temp);
  Serial.println(humi);

  if (isnan(temp) || isnan(humi)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  display.drawString(5, 10, "TEMP:" + String(temp, 2) + " Deg");
  display.drawString(5, 40, "HUMI:" + String(humi, 2) + " %");
  Serial.println("TEMP:" + String(temp, 2));
  Serial.println("HUMI:" + String(humi, 2));
  display.display();
}
