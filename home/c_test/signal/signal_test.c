#include "stdlib.h"
#include "stdio.h"
#include "signal.h"

static void SIGINT_cb_handler(int num)
{
    printf("\r\nSIGINT_cb_handler\r\n");
    exit(0);        //关闭当前进程
}

int main(void)
{
    signal( SIGINT , SIGINT_cb_handler);
    while(1)
    {
        sleep(1);
        printf("this is a signal test\r\n");
    }
    return 0 ;
}

