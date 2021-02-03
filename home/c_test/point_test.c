#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "unistd.h"
#include "sys/types.h"
#include "fcntl.h"


typedef struct 
{
    uint8_t d_len ;
    uint8_t *p_data ;
}data_t ;

int main( int argc , char *argv[] )
{
    data_t  data ;

    uint8_t group[3] = { 1 ,2,3 };

    data.d_len = 3;
    printf("data.d_len=%d\r\n", data.d_len);


//    data.p_data = malloc(sizeof(group));
//    memcpy( data.p_data , group , sizeof(group) );

    data.p_data = group ;
    memcpy( data.p_data , group , sizeof(group) );
    for( uint8_t i = 0 ; i < sizeof(group) ; i ++ )
    {
        printf("data.p_data[%d]=%d\r\n", i , data.p_data[i]);
    }

//    free(data.p_data);

}






