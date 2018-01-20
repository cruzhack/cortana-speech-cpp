//client.h
#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>

//error codes
#define RECIEVE_ERROR 2
#define SEND_ERROR 3
#define READ_ERROR 4

int recieve_audio_object(void);
int send_audio(void);
int convert_string(void);
int convert_to_object(void);

#endif