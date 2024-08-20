#include <Arduino.h>
#include "SPI.h"
#include <WiFi.h>
#include <WiFiMulti.h>
#include "Audio.h"
#include "HardwareSerial.h"

// WiFi credentials
#define WIFI_SSID ""
#define PASSWORD ""
#define OPENAI_API_KEY ""

// Configure I2S pins
#define I2S_LRC 25
#define I2S_DOUT 22
#define I2S_BCLK 26
#define I2S_MCLK 0

// UART pins
#define UART_RX 16
#define UART_TX 17

// Inits
WiFiMulti wifiMulti;
Audio audio;
HardwareSerial mySerial(2);

String result = "";

#define MAX_TEXT_LENGTH 1024

char uartStringArray[MAX_TEXT_LENGTH];

// Declaration
void audio_info(const char *info);

// Default
void setup() {
    Serial.begin(115200);

    // Wifi
    wifiMulti.addAP(WIFI_SSID, PASSWORD);
    Serial.println("Connecting to WiFi...");
    while (wifiMulti.run() != WL_CONNECTED) {
        delay(500);
    }
    Serial.print("Connected to WiFi\nIP: ");
    Serial.println(WiFi.localIP());

    mySerial.begin(9600, SERIAL_8N1, UART_RX, UART_TX);

    // Set up the audio
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT, -1);
    audio.setVolume(20); // 0...21
}

void loop() {
    // Check if data is available on UART
    if (mySerial.available()) {

      result = mySerial.readStringUntil('\n');
      // Ensure the result from UART fits within the array size
      if (result.length() < MAX_TEXT_LENGTH) {
        result.toCharArray(uartStringArray, MAX_TEXT_LENGTH);
      } else {
          Serial.println("Received string is too long to process");
        } 

      Serial.println("Updated result from UART: " + result);

      // Play the audio
      Serial.println("Calling speech api...");
      audio.connecttospeech(uartStringArray, "en");
    }

    // Keep the audio loop running
    audio.loop();
}

void audio_info(const char *info) {
    Serial.print("audio_info: ");
    Serial.println(info);
}
