#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#define  TRACE_MODULE    "event_queue_read.c"

#include "../trace.h"

int main(int argc,char *argv[])
{
    int fd;
    int err_code;
    char *filename = NULL;
    uint8_t read_buf[255];

    if(argc!=2)
    {
        trace_errorln("error input!");
        trace_infoln("usage: ./event_read /dev/xxx");
    }

    filename = argv[1];
    fd = open(filename,O_RDWR);
    if(fd < 0)
    {
        trace_errorln("can not open file %s",filename);
    }

    for(;;)
    {
        memset(read_buf,0,sizeof(read_buf));

        err_code = read(fd,read_buf,sizeof(read_buf));
        if(err_code > 0)
        {
            trace_debugln("receive event queue %d data:",err_code);
            trace_dump(read_buf,err_code);
        }
        else
        {
            trace_debugln("no any data in event queue");
        }
        sleep(1);
    }

    close(fd);
    trace_debugln("exit");
    return 0 ;
}


