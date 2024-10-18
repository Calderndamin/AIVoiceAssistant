# AIVoiceAssistant

## Overview

This system captures voice input, processes it using speech-to-text and text-to-speech services, and interacts with an OpenAI Language Model for advanced natural language understanding. The system employs **ESP32 microcontrollers** and Google APIs to perform the required tasks, transmitting data between hardware components and servers using Wi-Fi communication.

## Demos:

![Demo 1](https://youtube.com/shorts/IsUdmKDf1kA?si=Vv6fq5fXpZ6G2A-9)

![Demo 2](https://www.youtube.com/shorts/IsUdmKDf1kA)

## Components

### 1. **ESP32 A**
- **Function**: Captures voice input using a microphone sensor and sends it to the Google Speech-to-Text API.
- **Communication**: 
  - Connected to a voice input device via UART.
  - Sends the captured voice input to the Google Speech-to-Text API over Wi-Fi.
  - Receives processed text from the API and communicates it to a Node.js server for further processing.
  
### 2. **ESP32 B**
- **Function**: Outputs processed speech by receiving data from the Node.js server after interaction with the OpenAI Language Model.
- **Communication**: 
  - Receives processed text from the Node.js server via Wi-Fi.
  - Uses the Google Text-to-Speech API to convert the text back to speech.
  - Outputs the speech via a speaker module.

### 3. **Node.js Server**
- **Function**: Acts as the central hub for communication between the ESP32 modules, Google APIs, and the OpenAI Language Model.
  - **Input**: Receives text input from ESP32 A (processed by Google Speech-to-Text).
  - **Processing**: Sends the received text to the OpenAI Language Model for further processing, such as answering a query or generating a response.
  - **Output**: Forwards the processed text to ESP32 B to be converted to speech.

### 4. **Google Speech-to-Text API**
- **Function**: Converts voice input (captured by ESP32 A) into text. This text is sent to the Node.js server for further processing.

### 5. **Google Text-to-Speech API**
- **Function**: Converts text (received from the Node.js server) back into speech, which is played back by the speaker connected to ESP32 B.

### 6. **OpenAI Language Model**
- **Function**: Provides natural language understanding and generates responses based on the text input received from the Node.js server. This could involve answering questions, carrying out tasks, or processing commands.
  
## Workflow

![grafik](https://github.com/user-attachments/assets/4238fe97-7467-41df-8fde-26dc4ab83b10)

1. **Voice Input**: The system starts when the user speaks into the **voice input device** connected to **ESP32 A**.
2. **Speech to Text**: The voice input is sent over Wi-Fi to the **Google Speech-to-Text API**, which converts it into text.
3. **Text Processing**: The resulting text is sent to the **Node.js server**, where it is processed by the **OpenAI Language Model**. The model generates a suitable response based on the input.
4. **Text to Speech**: The response text is sent to **ESP32 B**, where it is forwarded to the **Google Text-to-Speech API** for conversion into speech.
5. **Voice Output**: The converted speech is output via the **speaker** connected to **ESP32 B**.

## Hardware

- **ESP32 A**: Microcontroller responsible for capturing voice input and sending it to the cloud.
- **ESP32 B**: Microcontroller responsible for receiving the processed text and outputting speech through the speaker.
- **IMNP441 Microphone Sensor**: Captures user voice for processing.
- **Speaker & MAX98357A Amplifier Module**: Outputs the processed voice response from the system.

## Software

- **Node.js Server**: Orchestrates communication between the ESP32 modules, Google APIs, and the OpenAI Language Model.
- **Google Cloud APIs**:
  - **Speech-to-Text**: Converts voice input to text.
  - **Text-to-Speech**: Converts text to voice output.
- **OpenAI Language Model**: Provides natural language processing to interpret and respond to user inputs.

---

### Future Enhancements
- Integration with more advanced sensors.
- Implementing local speech processing to reduce dependency on cloud services.

