//client.h
#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <curl/curl.h>

#define key_name "Ocp-Apim-Subscription-Key"
#define key1 "1f3639ec9c8c412297d971b87d44890a"
#define key2 "37645043a2a147eaa0d8ee6b7d0cfc29"
#define content_type "audio/wav; codec=audio/pcm; samplerate=16000"

#define RECIEVE_ERROR 2
#define SEND_ERROR 3
#define READ_ERROR 4


char * url;
char * uri;

char * response;

char * out_message;

static curlioerr my_ioctl(CURL *handle, curliocmd cmd, void *userp);

int recieve_audio_object(void);
int send_audio(void);
int convert_string(void);
int convert_to_object(void);

#endif