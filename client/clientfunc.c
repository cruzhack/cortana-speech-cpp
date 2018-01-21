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