#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "unistd.h"
#include "sys/types.h"
#include "fcntl.h"

#define BUF_MAX_SZ  1024
static uint8_t      m_rx_buff[BUF_MAX_SZ];
static uint16_t     m_rx_len = 0 ;

int main(int argc , char *argv[])
{
    int         fd ;
    int         err_code = 0 ;
    uint16_t    i = 0 ;
    ssize_t     rx_len = 0 ;

    fd = open( argv[1] , O_RDWR );
    if( fd < 0 )
    {
        printf("Error:file %s open fail\r\n",argv[i]);
        return -1 ;
    }

    sscanf(argv[2], "%u", &m_rx_len);
    printf("m_rx_len = %d ",m_rx_len);

    rx_len = read( fd , m_rx_buff , m_rx_len );

    if( rx_len < m_rx_len )
    {
        printf("ERROR: read err\r\n");
    }

    for(i = 0 ; i < m_rx_len ; i++)
    {
        printf("%02x" , m_rx_buff[i] );
    }
    printf("\r\n");

    err_code = close( fd );
    if( err_code < 0 )
    {
        printf("Fail: close to file %s  \n",argv[i] );
        return -1 ;
    }

    return 0; 
}


