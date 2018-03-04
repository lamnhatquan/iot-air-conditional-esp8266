#include <ESP8266WiFi.h>
#include "WiFiManager.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <WiFiManager.h>

IRsend irsend(4);  // An IR LED is controlled by GPIO4
//OFF:
uint16_t rawDataOFF[319] = {428, 444,  396, 474,  396, 472,  422, 446,  422, 446,  398, 25252,  3470, 1748,  424, 1316,  424, 444,  398, 472,  422, 446,  424, 1312,  428, 442,  398, 472,  396, 472,  424, 444,  422, 1314,  432, 440,  422, 1314,  428, 1310,  398, 472,  396, 1340,  424, 1314,  426, 1312,  424, 1314,  424, 1314,  424, 446,  396, 472,  398, 1340,  458, 412,  398, 470,  422, 446,  422, 446,  422, 446,  424, 444,  398, 472,  396, 472,  424, 444,  426, 444,  424, 444,  424, 444,  424, 444,  424, 446,  424, 446,  424, 446,  424, 446,  422, 446,  424, 444,  424, 444,  424, 446,  396, 472,  424, 1312,  426, 1312,  426, 444,  422, 446,  424, 446,  396, 1340,  426, 1312,  424, 448,  424, 444,  422, 1314,  424, 444,  424, 444,  424, 446,  424, 446,  420, 446,  424, 444,  424, 446,  424, 444,  424, 446,  422, 446,  424, 446,  422, 446,  422, 446,  398, 472,  424, 444,  408, 1330,  424, 444,  424, 1312,  428, 444,  422, 446,  422, 446,  424, 444,  424, 444,  424, 446,  424, 446,  396, 472,  424, 444,  422, 446,  424, 444,  398, 472,  424, 444,  424, 444,  398, 472,  424, 444,  426, 444,  424, 446,  426, 444,  396, 472,  426, 444,  422, 446,  424, 446,  422, 446,  424, 444,  424, 444,  424, 444,  398, 472,  422, 448,  424, 444,  422, 446,  424, 446,  396, 474,  424, 444,  424, 444,  424, 444,  424, 444,  424, 444,  426, 444,  422, 446,  424, 444,  426, 444,  424, 444,  426, 444,  424, 444,  424, 444,  424, 444,  424, 444,  424, 1312,  424, 446,  424, 1314,  426, 444,  424, 444,  424, 446,  424, 1312,  426, 1312,  460, 410,  424, 1312,  428, 444,  422, 1314,  426, 444,  424, 444,  424, 1312,  426, 446,  426, 442,  424, 446,  422, 446,  424, 1312,  460, 410,  398, 470,  426, 444,  424, 444,  424, 1312,  424, 1314,  424, 1312,  432, 1306,  430, 1308,  432, 440,  424, 444,  424, 446,  422};  // UNKNOWN 714A3816

//ON:
uint16_t rawDataON[319] = {460, 410,  432, 436,  430, 438,  430, 438,  432, 438,  432, 25216,  3482, 1736,  462, 1278,  436, 434,  432, 438,  432, 436,  432, 1304,  462, 410,  432, 438,  432, 438,  430, 438,  432, 1306,  462, 408,  430, 1306,  462, 1278,  434, 436,  430, 1306,  434, 1304,  434, 1304,  434, 1304,  434, 1304,  462, 410,  430, 438,  430, 1306,  434, 438,  430, 438,  430, 438,  430, 440,  430, 438,  430, 438,  432, 436,  430, 440,  432, 436,  432, 436,  432, 436,  432, 436,  434, 436,  432, 438,  432, 436,  430, 438,  432, 436,  432, 436,  432, 438,  430, 438,  434, 436,  430, 438,  430, 1308,  434, 1304,  430, 438,  432, 436,  430, 438,  430, 1308,  432, 1306,  436, 434,  430, 440,  430, 1306,  434, 436,  432, 438,  430, 438,  430, 438,  430, 438,  430, 438,  430, 440,  430, 438,  432, 436,  432, 438,  432, 436,  432, 436,  432, 438,  430, 438,  430, 438,  432, 1306,  434, 436,  430, 1306,  460, 410,  430, 438,  430, 438,  430, 438,  432, 436,  432, 438,  430, 440,  428, 438,  430, 438,  434, 434,  430, 438,  430, 438,  432, 436,  432, 438,  430, 438,  432, 436,  430, 440,  430, 438,  432, 438,  430, 436,  430, 440,  430, 438,  430, 438,  432, 438,  428, 440,  430, 438,  432, 438,  432, 436,  432, 436,  430, 438,  432, 436,  432, 438,  432, 436,  432, 438,  432, 438,  430, 438,  428, 440,  432, 438,  430, 438,  432, 436,  432, 438,  432, 436,  432, 436,  430, 438,  430, 438,  432, 436,  432, 438,  432, 438,  430, 1308,  430, 438,  430, 1308,  432, 436,  432, 438,  432, 436,  430, 1308,  434, 1304,  434, 438,  430, 1306,  434, 436,  430, 1306,  434, 436,  432, 436,  430, 1308,  432, 438,  430, 438,  430, 440,  432, 438,  430, 1308,  432, 438,  430, 438,  430, 438,  430, 438,  432, 1306,  458, 1282,  434, 1304,  434, 1304,  434, 1304,  434, 436,  430, 438,  430, 438,  430};  // UNKNOWN 714A3816

void setup()

{
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  // WiFiManager wifiManager;
  // wifiManager.autoConnect("AirConditional-IoT");
  // Serial.print("connected to");
  // Serial.println(WiFi.localIP());
}

void loop()
{
  irsend.sendRaw(rawDataOFF, 319, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
  irsend.sendRaw(rawDataON, 319, 38);  // Send a raw data capture at 38kHz.
  delay(2000);
//  irsend.sendRaw(rawDataOf/f, 199, 38);  // Send a raw data capture at 38kHz.
//  delay(5000);/
}
