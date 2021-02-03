#include <stdio.h>
#include "unistd.h"
#include "sys/types.h"
#include "fcntl.h"
#include "stdlib.h"
#include "string.h"

#include "../user_util.h"

typedef enum 
{
    false,
    true,
}bool ;


/*
 * @brief main  
 */
int main(int argc , char *argv[])
{
    int fd ;
    int err_code = 0 ;

    uint8_t  tx_buff[1];

    if( 3 != argc )
    {
        printf("Error usage ! \n");
        return -1 ;
    }

    char *filename = argv[1] ;

    fd = open( filename , O_RDWR );
    if( fd < 0 )
    {
        printf("Fail:file %s open \n",filename );
        return -1 ;
    }

    tx_buff[0]  = atoi( argv[2] );

    err_code = write( fd , tx_buff , sizeof(tx_buff) );
    if( err_code < 0 )
    {
        printf("Fail : write data into drv file\n");
        close(fd);
        return -1 ;
    }
    printf("Success:write data to drv file\n");

    err_code = close( fd );
    if( err_code < 0 )
    {
        printf("Fail: close to file %s  \n",filename );
        return -1 ;
    }

    return 0 ;
}











