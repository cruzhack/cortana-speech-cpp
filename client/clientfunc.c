/*clientfunc.c
here client functions are implmented*/
#include "client.h"

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
int post_request(CURLcode response, char * url, char * post_data)
{
    CURL *curl;
    curl = curl_easy_init();
    if (!curl)
    {
        return INVALID_CURL;
    }
    //POST url
    curl_easy_setopt(curl, CURLOPT_URL, url);
    //POST data
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
 
    response = curl_easy_perform(curl);
    //response error 
    if(response != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(response));
        return RESPONSE_ERROR;
    }
    /* always cleanup */ 
    curl_easy_cleanup(curl);
    return SUCCESS;
}
//composes post request into a character array and returns the output size
int compose_request(void)
{
    char * out = (char*)malloc(1024*(sizeof(char)));
    strcat(out, ACCEPT);
    strcat(out, CONTENT_TYPE);
    strcat(out, KEY1);
    strcat(out, HOST);
    strcat(out, TRANSFER);
    strcat(out, EXPECT);
    printf("%s\n",out);
    free(out);
    return -1;
}