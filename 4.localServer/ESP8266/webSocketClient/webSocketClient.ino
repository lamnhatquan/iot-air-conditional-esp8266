#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> //https://github.com/Links2004/arduinoWebSockets
WebSocketsClient webSocket;

const char* ssid = "The Coffee House";
const char* password = "thecoffeehouse";
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
      if(strcmp((char*)payload, "BTN_20_PRESSED") == 0) {
        digitalWrite(LED_20_DEG, 1); // Khi client (web-browser) phát sự kiện "BTN_20_PRESSED" thì server sẽ broadcast gói tin đến ESP8266
      } else if(strcmp((char*)payload, "BTN_30_PRESSED") == 0) { 
        digitalWrite(LED_30_DEG, 1);
      } else if(strcmp((char*)payload, "BTN_ONOFF_PRESSED") == 0) {
        digitalWrite(LED_20_DEG, 0);
        digitalWrite(LED_30_DEG, 0);
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  
  pinMode(LED_20_DEG, OUTPUT);
  pinMode(LED_30_DEG, OUTPUT);
  pinMode(BTN, INPUT);
  Serial.begin(115200);
  Serial.println("ESP8266 Websocket Client");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("connected");
  webSocket.begin("10.237.219.224", 8000);// IP address của máy tính khi kết nối cùng 1 network wifi với ESP8266
  webSocket.onEvent(webSocketEvent);
}

void loop() {
  webSocket.loop();
  static bool isPressed = false;
  if (!isPressed && digitalRead(BTN) == 0) { //Nhấn nút nhấn GPIO0
    isPressed = true;
    webSocket.sendTXT("BTN_PRESSED");
  } else if (isPressed && digitalRead(BTN)) { //Nhả nút nhấn GPIO0
    isPressed = false;
    webSocket.sendTXT("BTN_RELEASE");
  }
}
