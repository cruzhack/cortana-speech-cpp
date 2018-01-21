/*clientfunc.c
here client functions are implmented*/
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int recieve_audio_object(void)
{
    return -1;
}
int send_audio(void)
{
    return -1;
}
int convert_string(void)
{
    return -1;
}
int convert_to_object(void)
{
    return -1;
}
//perform a request and return the response to res
CURLcode post_request(char *url, char *post_data)
{
    CURLcode response;
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        printf("invalid curl\n");
    }
    //POST url
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);

    response = curl_easy_perform(curl);
    //response error
    if (response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(response));
        return RESPONSE_ERROR;
    }
    /* always cleanup */
    curl_easy_cleanup(curl);
    return response;
}
//http get request
CURLcode get_request()
{
    CURLcode response;
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        printf("invalid curl\n");
    }
    curl_easy_setopt(curl, CURLOPT_URL, URI);
    response = curl_easy_perform(curl);
    if (response != CURLE_OK)
    {
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(response));
    }
    return response;
}

//composes post request into a character array and returns the output size
int compose_request(char *out)
{
    int size = sizeof(ACCEPT) + sizeof(CONTENT_TYPE) + sizeof(KEY1) + sizeof(HOST) + sizeof(TRANSFER) + sizeof(EXPECT);
    strcat(out, ACCEPT);
    strcat(out, CONTENT_TYPE);
    strcat(out, KEY1);
    strcat(out, HOST);
    strcat(out, TRANSFER);
    strcat(out, EXPECT);
    printf("%s\n", out);
    return size;
    //free(out);
    //return -1;
}


char* get_raw_data(char* filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) return NULL;

    // Get File size
    char b = getc(fp);
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    printf("Size of file is %d\n", size);
    char bytes[size + 1];
    
    // Read File
    // fread(bytes, 1, sizeof bytes, fp);
    // fclose(fp);
    // bytes[size] = '\0';
    size_t nread;
    while ((nread = fread(bytes, 1, sizeof bytes, fp)) > 0)
        fwrite(bytes, 1, nread, stdout);
    if (ferror(fp)) {
        /* deal with error */
    }
    fclose(fp);

    //Print Result
    printf("Got raw data as %s\n", bytes);
    for(int i = 0; i < size + 1; i++) {
        printf("%d ", bytes[i]);
    }
    printf("\n");


    return bytes;
}