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
    char * output;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    //curl 
    // get the body string size
   

    /* get a curl handle */

    output = compose_request();
    //post_request(curl, res, output);
    curl_global_cleanup();
    return 0;
}
