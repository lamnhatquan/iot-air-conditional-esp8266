#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SSD1306.h"
#include "WiFiManager.h"
#include <WebSocketsClient.h> //https://github.com/Links2004/arduinoWebSockets
#include "DHT.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#define DHTPIN 10
#define DHTTYPE DHT11

WebSocketsClient webSocket;
DHT dht(DHTPIN, DHTTYPE);
SSD1306  display(0x3c, 4, 5);
IRsend irsend(15);  // An IR LED is controlled by GPIO4

unsigned long previousMillis = 0;
const long interval = 3000;
//const char* ssid = "The Coffee House";
//const char* password = "thecoffeehouse";
//const char* ssid = "iotmaker.vn";
//const char* password = "@iotmaker.vn";
const int LED_20_DEG = 13;
const int LED_30_DEG = 14;
const int BTN = 0;
uint16_t rawDataOff[199] = {4492, 4374, 608, 1550, 568,  512,  566, 1588, 568, 1588, 570, 512,
                            566, 512,  566, 1588, 582,  500,  566, 512,  566, 1588, 568, 512,
                            566, 512,  564, 1588, 568,  1590, 568, 512,  566, 1588, 568, 512,
                            566, 1588, 570, 1586, 568,  1588, 568, 1588, 580, 526,  540, 1590,
                            564, 1590, 568, 1588, 568,  512,  566, 512,  566, 512,  566, 510,
                            566, 1588, 568, 512,  566,  510,  566, 1590, 568, 1590, 568, 1588,
                            568, 512,  566, 512,  566,  510,  566, 512,  566, 512,  566, 512,
                            564, 512,  566, 512,  566,  1590, 578, 1578, 568, 1588, 584, 1572,
                            568, 1588, 568, 5588, 4466, 4368, 594, 1562, 568, 512,  566, 1590,
                            568, 1586, 568, 512,  566,  510,  566, 1588, 606, 500,  540, 512,
                            566, 1588, 568, 512,  566,  512,  566, 1590, 568, 1588, 568, 512,
                            566, 1588, 568, 510,  566,  1588, 568, 1586, 568, 1588, 568, 1590,
                            574, 534,  536, 1588, 568,  1588, 568, 1586, 594, 518,  536, 510,
                            566, 542,  534, 512,  566,  1588, 566, 512,  566, 512,  566, 1588,
                            568, 1588, 568, 1586, 578,  532,  536, 512,  566, 510,  566, 512,
                            566, 512,  566, 512,  566,  510,  566, 512,  566, 1588, 578, 1576,
                            568, 1588, 578, 1578, 568,  1588, 568
                           };  // COOLIX B27BE0

uint16_t rawData20[199] = {4494, 4368, 610, 1546, 498,  582,  494, 1658, 496, 1660, 608, 470,
                           494,  582,  496, 1656, 610,  470,  494, 584,  494, 1658, 496, 584,
                           494,  582,  494, 1658, 610,  1548, 608, 470,  494, 1658, 496, 1662,
                           608,  470,  494, 1658, 612,  1544, 586, 1570, 610, 1546, 496, 1660,
                           496,  1658, 610, 470,  494,  1658, 610, 470,  494, 582,  494, 584,
                           494,  584,  494, 582,  494,  584,  494, 584,  494, 584,  494, 1658,
                           496,  584,  494, 584,  494,  582,  494, 582,  494, 584,  494, 1660,
                           496,  1660, 494, 584,  494,  1658, 610, 1546, 496, 1660, 610, 1546,
                           496,  1660, 496, 5656, 4470, 4360, 498, 1658, 496, 584,  494, 1660,
                           496,  1660, 496, 582,  494,  584,  494, 1660, 498, 580,  496, 584,
                           494,  1660, 494, 584,  494,  584,  494, 1660, 496, 1660, 610, 468,
                           494,  1660, 610, 1546, 498,  582,  494, 1660, 610, 1544, 496, 1660,
                           610,  1546, 496, 1660, 496,  1660, 496, 584,  494, 1658, 496, 584,
                           494,  582,  494, 584,  494,  584,  494, 582,  494, 584,  494, 584,
                           494,  582,  494, 1658, 496,  584,  494, 584,  494, 582,  494, 584,
                           494,  582,  494, 1660, 496, 1660,  496, 584,  494, 1658, 608, 1548,
                           608,  1546, 496, 1660, 496, 1660,  494
                          };  // COOLIX B2BF20

uint16_t rawData30[199] = {4498,  4380, 606,  1554, 570,  514,  566,  1592, 568,  1592, 568,  512,
                           566,   512,  566,  1590, 578,  532,  538,  514,  566,  1590, 570,  514,
                           566,   514,  566,  1590, 578,  1582, 568,  512,  566,  1590, 570,  512,
                           566,   512,  568,  512,  566,  1590, 578,  1580, 568,  1590, 570,  1590,
                           578,   1582, 568,  1592, 570,  1590, 568,  1588, 570,  514,  566,  512,
                           566,   516,  564,  514,  566,  512,  566,  1590, 570,  512,  566,  1590,
                           568,   1590, 568,  1592, 570,  512,  566,  544,  536,  540,  538,  512,
                           566,   1590, 568,  512,  566,  516,  564,  514,  564,  1592, 576,  1580,
                           570,   1590, 568,  5594, 4458, 4386, 594,  1566, 568,  512,  566,  1592,
                           568,   1592, 568,  512,  566,  512,  566,  1590, 568,  542,  536,  514,
                           564,   1592, 568,  512,  566,  512,  566,  1592, 568,  1592, 566,  514,
                           566,   1590, 578,  504,  566,  514,  566,  512,  566,  1592, 568,  1588,
                           570,   1590, 568,  1588, 576,  1584, 566,  1590, 570,  1590, 568,  1590,
                           568,   512,  566,  512,  566,  514,  566,  514,  566,  512,  566,  1588,
                           570,   514,  566,  1590, 568,  1590, 568,  1592, 568,  512,  566,  514,
                           566,   514,  566,  512,  566,  1590, 568,  514,  566,  514,  566,  512,
                           566,   1590, 568,  1588, 578,  1580, 570
                          };  // COOLIX B21FB8

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
        irsend.sendRaw(rawData20, 199, 38);
        digitalWrite(LED_20_DEG, 1); // Khi client (web-browser) phát sự kiện "BTN_20_PRESSED" thì server sẽ broadcast gói tin đến ESP8266
      } else if (strcmp((char*)payload, "BTN_30_ON") == 0) {
        digitalWrite(LED_30_DEG, 1);
        irsend.sendRaw(rawData30, 199, 38);
      } else if (strcmp((char*)payload, "BTN_ONOFF_PRESSED") == 0) {
        irsend.sendRaw(rawDataOff, 199, 38);
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

  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  //  Init Serial
  //  Serial.begin(115200);
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
  webSocket.begin("10.243.103.224", 8000);  // IP address your computer
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

