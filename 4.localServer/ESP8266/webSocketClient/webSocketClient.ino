#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SSD1306.h"
#include "WiFiManager.h"
#include <WebSocketsClient.h> //https://github.com/Links2004/arduinoWebSockets
#include "DHT.h"
#define DHTPIN 10
#define DHTTYPE DHT11

WebSocketsClient webSocket;
DHT dht(DHTPIN, DHTTYPE);
SSD1306  display(0x3c, 4, 5);

unsigned long previousMillis = 0;
const long interval = 3000;
const char* ssid = "The Coffee House";
const char* password = "thecoffeehouse";
//const char* ssid = "iotmaker.vn";
//const char* password = "@iotmaker.vn";
const int LED_20_DEG = 13;
const int LED_30_DEG = 14;
const int BTN = 0;

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      {
        Serial.printf("[WSc] Connected to url: %s\n",  payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[WSc] get text: %s\n", payload);
      if (strcmp((char*)payload, "BTN_20_ON") == 0) {
        digitalWrite(LED_20_DEG, 1); // Khi client (web-browser) phát sự kiện "BTN_20_PRESSED" thì server sẽ broadcast gói tin đến ESP8266
      } else if (strcmp((char*)payload, "BTN_30_ON") == 0) {
        digitalWrite(LED_30_DEG, 1);
      } else if (strcmp((char*)payload, "BTN_ONOFF_PRESSED") == 0) {
        digitalWrite(LED_20_DEG, 0);
        digitalWrite(LED_30_DEG, 0);
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}
void setupWifi()
{
  WiFiManager wifiManager;
  Serial.println("Wifi Manager");
  Serial.println("Connecting");

  display.clear();
  display.drawString(10, 10, "Wifi Manager");
  display.drawString(0, 30, "Access-your-network");
  display.display();
  delay(3000);
  //  if (!wifiManager.autoConnect("IOTMAKER_" + String(ESP.getChipId()).c_str())) {
  if (!wifiManager.autoConnect(("IOTMAKER_" + String(ESP.getChipId())).c_str())) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  }
  display.clear();
  display.drawString(20, 20, "Connected");
  display.display();
  delay(2000);
  Serial.print("Connect to your SSID network:\t");
  String yourSSID = ("IOTMAKER_" + String(ESP.getChipId())).c_str();
  Serial.println(yourSSID);
  Serial.println("Access to local IP 192.168.4.1 -> Configure Wifi");

}

void setup() {

  //  Config I/O
  pinMode(LED_20_DEG, OUTPUT);
  pinMode(LED_30_DEG, OUTPUT);
  pinMode(BTN, INPUT);

  //  Init Serial
  Serial.begin(115200);
  Serial.println("ESP8266 Websocket Client");

  //  Init OLED to display
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.flipScreenVertically();
  display.drawString(5, 10, "Internet of Things");
  display.drawString(40, 30, "IoT A/C");
  display.display();
  delay(5000);
  
  // Init dht
  dht.begin();
  
  // Init and connect to Wifi using Wifi Manager
  setupWifi();
  
  //  Init webcocket client
  webSocket.begin("10.237.219.224", 8000);  // IP address your computer
  webSocket.onEvent(webSocketEvent);
}

void loop()
{
  webSocket.loop();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    display.clear();
    previousMillis = currentMillis;
    float temp = dht.readTemperature();
    float humi = dht.readHumidity();
    if (isnan(temp) || isnan(humi)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    String dataDHT =  "{\"temp\":" + String(temp) + ",\"humi\":" + String(humi) + "}"; // Send data format JSON {"temp":"23.00","humi":"57.00"}
    Serial.println(dataDHT);
    webSocket.sendTXT(dataDHT);

    //Display to OLED
    display.drawString(5, 10, "TEMP:" + String(temp, 2) + " Deg");
    Serial.println("TEMP:" + String(temp, 2));
    display.drawString(5, 40, "HUMI:" + String(humi, 2) + " %");
    Serial.println("HUMI:" + String(humi, 2));
    display.display();
  }
}

