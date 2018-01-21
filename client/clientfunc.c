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

struct string {
  char *ptr;
  size_t len;
};

static void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

static void cleanup(CURL* curl){
    if(curl != NULL) curl_easy_cleanup(curl);
    curl_global_cleanup();
}

//http get request
CURLcode get()
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

static size_t write_callback(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
    printf("\n\n\n READ CALLBACK \n\n\n");
    struct WriteThis *wt = (struct WriteThis *)userp;
    size_t buffer_size = size*nmemb;
 
    if(wt->sizeleft) {
        /* copy as much as possible from the source to the destination */ 
        size_t copy_this_much = wt->sizeleft;
        if(copy_this_much > buffer_size)
        copy_this_much = buffer_size;
        memcpy(dest, wt->readptr, copy_this_much);
        for(int i = 0; i < copy_this_much; i++){
            printf("%c", wt->readptr[i]);
        }
        wt->readptr += copy_this_much;
        wt->sizeleft -= copy_this_much;
        return copy_this_much; /* we copied this many bytes */ 
    }
    
    return 0; /* no more data left to deliver */ 
}

CURLcode post(char* data) {
    CURL *curl;
    CURLcode res; 
    struct WriteThis wt;
    
    wt.readptr = data;
    wt.sizeleft = strlen(data);
    
    /* In windows, this will init the winsock stuff */ 
    res = curl_global_init(CURL_GLOBAL_DEFAULT);
    /* Check for errors */ 
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_global_init() failed: %s\n", curl_easy_strerror(res));
    }
    
    /* get a curl handle */ 
    curl = curl_easy_init();
    if(!curl) {
        fprintf(stderr, "curl_easy_init() failed: %s\n", curl_easy_strerror(res));
    }
    /* First set the URL that is about to receive our POST. */ 
    curl_easy_setopt(curl, CURLOPT_URL, URI);

    /* Now specify we want to POST data */ 
    curl_easy_setopt(curl, CURLOPT_POST, 1L);

    /* we want to use our own read function */ 
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);

    struct string s;
    init_string(&s);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

    /* pointer to pass to our read function */ 
    curl_easy_setopt(curl, CURLOPT_READDATA, &wt);

    /* get verbose debug output please */ 
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen(data)); 

    /**
     * Set Headers
     */

    struct curl_slist *chunk = NULL;

    chunk = curl_slist_append(chunk, TRANSFER);
    chunk = curl_slist_append(chunk, CONTENT_TYPE);
    chunk = curl_slist_append(chunk, ACCEPT);
    chunk = curl_slist_append(chunk, EXPECT);
    chunk = curl_slist_append(chunk, KEY1);

    res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
    printf("RESPONSE: %s\nEND RESPONSE\n", s.ptr);
    free(s.ptr);

    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    }

    /* always cleanup */ 
    cleanup(curl);

    return res;
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