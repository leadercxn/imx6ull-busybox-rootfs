#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "unistd.h"
#include "sys/types.h"
#include "fcntl.h"


#include "../user_util.h"
#include "../timer_cmd.h"

#define  TRACE_MODULE    "tim.c"

#include "../trace.h"

#define BUF_MAX_SZ  1024

static uint8_t      m_tx_buff[BUF_MAX_SZ];
static uint16_t     m_tx_len = 0 ;

static void usage(void)
{
    printf("    usage: ./tim  file_name  cmd  [data] \r\n");
    printf("    Available option cmd:\r\n");
    printf("    -h              printf this app help\r\n");
    printf("    -a <uint32>     add a timer and start with <uint32> tick\r\n");
    printf("    -d              del the timer \r\n");
    printf("    -m <uint32>     moditify the timer <uint32> tick\r\n");
    printf("\r\n");
}

/**
 * @brief main  
 */
int main(int argc , char *argv[])
{
    int         fd ;
    int         err_code = 0 ;
    uint8_t     i = 0 ;
    uint32_t    expires = 0 ;
    char        *filename = NULL ;
    
    memset( m_tx_buff , BUF_MAX_SZ , 0 );

    if(argc > 4)
    {
        trace_errorln("please input correct usage");
        usage();
        return -1;
    }

    m_tx_buff[m_tx_len] = 1 ;
    m_tx_len ++ ;

    for(i=1;i<argc;)
    {
        if( strcmp(argv[i], "-h") == 0 )
        {
            usage();
            return 0;
        }
        else if( (strncmp ( argv[i],"-", 1 ) == 0) && ( i == 1 ) )
        {
            trace_errorln("please input correct usage");
            usage();
            return -1;
        }
        else if( i == 1 )
        {
            filename = argv[i] ;

            fd = open( filename , O_RDWR );
            if( fd < 0 )
            {
                trace_errorln("file %s open fail", filename );
                return -1 ;
            }

            i++;
        }
        else if( strcmp(argv[i], "-a") == 0 )
        {
            i++;
            sscanf(argv[i], "%u", &expires);
            i++;
            
            m_tx_buff[m_tx_len] = CMD_START ;
            m_tx_len ++ ;
            break;
        }
        else if( strcmp(argv[i], "-d") == 0 )
        {
            i++;
            m_tx_buff[m_tx_len] = CMD_STOP ;
            break;
        }
        else if( strcmp(argv[i], "-m") == 0 )
        {
            i++;
            sscanf(argv[i], "%u", &expires);
            i++;

            m_tx_buff[m_tx_len] = CMD_MODIFY ;
            m_tx_len ++ ;
            break;
        }
    }

    if( i > 3 ) //命令带了参数
    {
        m_tx_buff[m_tx_len] = sizeof(uint32_t) ;
        m_tx_len ++ ;
    }

    memcpy( &m_tx_buff[m_tx_len] , &expires , sizeof(uint32_t) );
    m_tx_len += sizeof(uint32_t)  ;

    err_code = write( fd , m_tx_buff , m_tx_len );
    if( err_code < 0 )
    {
        trace_errorln("write data into drv file");
        close(fd);
        return -1 ;
    }

    trace_info("the tx buf data: ");
    trace_dump( m_tx_buff , m_tx_len );

    err_code = close( fd );
    if( err_code < 0 )
    {
        trace_error("Fail: close to file %s  \n",filename );
        return -1 ;
    }

    return 0 ;
}











