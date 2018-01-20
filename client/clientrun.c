//the main file that runs the client
#include "client.h"

int main(void)
{
    CURLcode res;

    curl_global_init(CURL_GLOBAL_ALL);

    /* get a curl handle */

    compose_request();
    //post_request(curl, res);
    curl_global_cleanup();
    return 0;
}
