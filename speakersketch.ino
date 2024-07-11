const int dacPin = 25;  // Choose a DAC pin (GPIO25 or GPIO26)

// Example PCM data buffer for voice
const uint8_t pcmData[] = {
  128, 132, 136, 140, 144, 148, 152, 156, 160, 164, 168, 172, 176, 180, 184, 188,
  192, 196, 200, 204, 208, 212, 216, 220, 224, 228, 232, 236, 240, 244, 248, 252,
  // Add more data as needed
};

const int pcmDataLength = sizeof(pcmData) / sizeof(pcmData[0]);

void setup() {
  Serial.begin(115200);
  // No additional setup required for DAC
}

void loop() {
  for (int i = 0; i < pcmDataLength; i++) {
    dacWrite(dacPin, pcmData[i]);  // Output PCM data to DAC
    delayMicroseconds(125);  // Adjust delay for the sample rate (e.g., 8 kHz -> 125µs per sample)
  }
  delay(1000);  // Pause before repeating the voice output
}
