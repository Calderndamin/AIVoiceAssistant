var fs = require("file-system");
const http = require("http");
const server = http.createServer();
const fileName = "./resources/recording.wav";
const path = require("path");

server.on("request", (request, response) => {
	if (request.method == "POST" && request.url === "/upload") {
		var recordingFile = fs.createWriteStream(fileName, { encoding: "utf8" });
		request.on("data", function(data) {
			recordingFile.write(data);
		});

		request.on("end", async function() {
			recordingFile.end();
			const transciption = await speechToTextAPI();
			response.writeHead(200, { "Content-Type": "text/plain" });
			response.end(transciption);
		});
	} else {
		console.log("Error Check your POST request");
		response.writeHead(405, { "Content-Type": "text/plain" });
	}
});

async function speechToTextAPI() {
	// Imports the Google Cloud client library
	const speech = require("@google-cloud/speech");
	const fs = require("fs");

	// Creates a client
	const client = new speech.SpeechClient();

	// Reads a local audio file and converts it to base64
	const file = fs.readFileSync(fileName);
	const audioBytes = file.toString("base64");

	// The audio file's encoding, sample rate in hertz, and BCP-47 language code
	const audio = {
		content: audioBytes
	};
	const config = {
		encoding: "LINEAR16",
		sampleRateHertz: 16000,
		languageCode: "en-US"
	};
	const request = {
		audio: audio,
		config: config
	};

	// Detects speech in the audio file
	const [response] = await client.recognize(request);
	const transcription = response.results.map((result) => result.alternatives[0].transcript).join("\n");
	console.log(`Transcription: ${transcription}`);
	return OpenAIAPI(transcription);
}

require('dotenv').config();
const { OpenAI } = require('openai');

// Initialize the OpenAI client with the API key
const openai = new OpenAI({
  apiKey: "", // Ensure this matches your .env file variable
});

async function OpenAIAPI(mytransciption) {
  const completion = await openai.chat.completions.create({
    messages: [{ role: "system", content: mytransciption }],
    model: "gpt-4o",
    max_tokens: 32,
    temperature: 0.8,
  });

  const answer = completion.choices[0].message.content;
  console.log(answer);
  //NewSpeechAPI(answer);
  return answer;
}

const speechFile = path.resolve("./speech.mp3");

async function NewSpeechAPI(inputtext) {
  const mp3 = await openai.audio.speech.create({
    model: "tts-1",
    voice: "shimmer",
    input: inputtext,
  });
  console.log(speechFile);
  const buffer = Buffer.from(await mp3.arrayBuffer());
  await fs.promises.writeFile(speechFile, buffer);
}


const port = 8888;
server.listen(port);
console.log(`Listening at ${port}`);