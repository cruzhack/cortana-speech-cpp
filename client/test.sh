










curl -X POST "https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en-us&format=detailed" -H "Transfer-Encoding: chunked" -H "Ocp-Apim-Subscription-Key: 1f3639ec9c8c412297d971b87d44890a" -H "Content-type: audio/wav; codec=audio/pcm; samplerate=16000" --data-binary @HelloWorld.wav
