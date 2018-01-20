//client.h
#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h>

#define end "\0"
#define ACCEPT "Accept: application/json;text/xml"
#define KEY1 " Ocp-Apim-Subscription-Key 1f3639ec9c8c412297d971b87d44890a"
#define KEY2 "37645043a2a147eaa0d8ee6b7d0cfc29"
#define CONTENT_TYPE "Content-Type: audio/wav; codec=audio/pcm; samplerate=16000 "
#define HOST " Host: speech.platform.bing.com"
#define TRANSFER " Transfer-Encoding: chunked"
#define EXPECT " Expect: 100-continue"
#define uri "https://speech.platform.bing.com/speech/recognition/interactive/cognitiveservices/v1?language=en-US";

#define SUCCESS 0
#define RECIEVE_ERROR 2
#define SEND_ERROR 3
#define READ_ERROR 4
#define INVALID_CURL 5
#define RESPONSE_ERROR 6


char *response;

char *out_message;

int recieve_audio_object(void);
int send_audio(void);
int post_request(CURLcode response, char * url, char * post_data);
int compose_request(void);



#endif