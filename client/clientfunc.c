/*clientfunc.c
here client functions are implmented*/
#include "client.h"
static curlioerr my_ioctl(CURL *handle, curliocmd cmd, void *userp)
{

    int *fdp = (int *)userp;
    int fd = *fdp;

    (void)handle; /* not used in here */

    switch (cmd)
    {
    case CURLIOCMD_RESTARTREAD:
        /* mr libcurl kindly asks as to rewind the read data stream to start */
        if (-1 == lseek(fd, 0, SEEK_SET))
            /* couldn't rewind */
            return CURLIOE_FAILRESTART;

        break;

    default: /* ignore unknown commands */
        return CURLIOE_UNKNOWNCMD;
    }
    return CURLIOE_OK; /* success! */
}

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