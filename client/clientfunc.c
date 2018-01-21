/*clientfunc.c
here client functions are implmented*/
#include "client.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct WriteThis {
    const char* readptr;
    size_t sizeleft;
};

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

static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
  struct WriteThis *wt = (struct WriteThis *)userp;
  size_t buffer_size = size*nmemb;
 
  if(wt->sizeleft) {
    /* copy as much as possible from the source to the destination */ 
    size_t copy_this_much = wt->sizeleft;
    if(copy_this_much > buffer_size)
      copy_this_much = buffer_size;
    memcpy(dest, wt->readptr, copy_this_much);
 
    wt->readptr += copy_this_much;
    wt->sizeleft -= copy_this_much;
    return copy_this_much; /* we copied this many bytes */ 
  }
 
  return 0; /* no more data left to deliver */ 
}

void post(char* data) {
    CURL *curl;
    CURLcode res;
 
    struct WriteThis wt;
    
    wt.readptr = data;
    wt.sizeleft = strlen(data);
    
    /* In windows, this will init the winsock stuff */ 
    res = curl_global_init(CURL_GLOBAL_DEFAULT);
    /* Check for errors */ 
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_global_init() failed: %s\n",
                curl_easy_strerror(res));
        return 1;
    }
    
    /* get a curl handle */ 
    curl = curl_easy_init();
    if(curl) {
        /* First set the URL that is about to receive our POST. */ 
        curl_easy_setopt(curl, CURLOPT_URL, URI);
    
        /* Now specify we want to POST data */ 
        curl_easy_setopt(curl, CURLOPT_POST, 1L);
    
        /* we want to use our own read function */ 
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    
        /* pointer to pass to our read function */ 
        curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
    
        /* get verbose debug output please */ 
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    
        /*
        If you use POST to a HTTP 1.1 server, you can send data without knowing
        the size before starting the POST if you use chunked encoding. You
        enable this by adding a header like "Transfer-Encoding: chunked" with
        CURLOPT_HTTPHEADER. With HTTP 1.0 or without chunked transfer, you must
        specify the size in the request.
        */ 
    
        struct curl_slist *chunk = NULL;
    
        chunk = curl_slist_append(chunk, TRANSFER);
        res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        /* use curl_slist_free_all() after the *perform() call to free this
            list again */ 
    
        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);
        /* Check for errors */ 
        if(res != CURLE_OK)
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
                curl_easy_strerror(res));
    
        /* always cleanup */ 
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}

char* get_raw_data(char* filename) {
    FILE* fp = fopen(filename, "r");
    if(fp == NULL) return NULL;

    // Get File size
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    char* bytes = (char*) malloc(size + 1);

    // Reset file pointer
    fclose(fp);
    fp = fopen(filename, "r");
    
    // Read File
    char b = fgetc(fp);
    int i = 0;
    while(b != EOF) {
        bytes[i++] = b;
        b = fgetc(fp);
    }
    bytes[i] = '\0';
    fclose(fp);


    printf("Got raw data as %s\n", bytes);
    return bytes;
}