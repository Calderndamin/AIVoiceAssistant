#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "ssid";
const char* password = "password";
const char* chatgpt_token = "token";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  while(!Serial);

  // wait for WiFi connection
  WiFi.begin(ssid, password);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Please enter your question:");
}

void loop() {
  if (Serial.available() > 0) {
    String userQuestion = Serial.readStringUntil('\n');
    userQuestion.trim();  // Remove any trailing newline characters
    Serial.print(userQuestion);
    
    HTTPClient https;

    Serial.print("[HTTPS] begin...\n");
    if (https.begin("https://api.openai.com/v1/chat/completions")) {  // HTTPS
      
      https.addHeader("Content-Type", "application/json"); 
      String token_key = String("Bearer ") + chatgpt_token;
      https.addHeader("Authorization", token_key);
      
      String payload = "{\"model\": \"gpt-3.5-turbo\",";
      payload += "\"messages\": [";
      payload += "{";
      payload += "\"role\": \"user\",";
      payload += "\"content\": \"" + userQuestion + "\"";
      payload += "}";
      payload += "],"; 
      payload += "\"temperature\": 1,";
      payload += "\"max_tokens\": 128,";
      payload += "\"top_p\": 1,";
      payload += "\"frequency_penalty\": 0,";
      payload += "\"presence_penalty\": 0}";

      Serial.print("[HTTPS] POST...\n");
      
      int httpCode = https.POST(payload);

      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        String response = https.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, response);
        String answer = doc["choices"][0]["message"]["content"];

        Serial.println("Response from ChatGPT:");
        Serial.println(answer);
      } else {
        Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }
      https.end();
    } else {
      Serial.printf("[HTTPS] Unable to connect\n");
    }
    Serial.println("Please enter your next question:");
  }
  delay(100);  // Small delay to avoid overwhelming the loop
}
