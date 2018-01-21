//the main file that runs the client
#include "client.h"

/* TODO
get size of body string
add header uri
send combined POST 
have a recieving function loop listinging to incoming messages
*/

int main(void)
{
    // char * output  = (char *)malloc(1024 * (sizeof(char)));
    // CURLcode res;
    // curl_global_init(CURL_GLOBAL_ALL);
    // //curl
    // // get the body string size
   

    // /* get a curl handle */

    // size_t size = compose_request(output);
    // printf("%zu \n", size);
    // printf("here\n");
    // free(output);
    // printf("here\n");
    // //post_request(curl, res, output);
    // curl_global_cleanup();

    char* data = get_raw_data("HelloWorld.wav");
    post(data);
    
    // char * req = (char *)malloc(1024 * sizeof(char));
    // int req_size = compose_request(req);
    // printf("returned req \n%s\n", req);
    // free (req);
    return 0;
}
