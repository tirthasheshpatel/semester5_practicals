#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "protocol.h"

void _file_from_network_layer( packet *p )
{
    size_t filelen;
    FILE* fp = fopen( getenv( "INPUT_FILE" ), "rb" );

    if ( fp == NULL ) {
        fprintf( stderr , "error while opening '%s'.\nplease make sure the file exists!\n", getenv( "INPUT_FILE" ) );
        exit( 1 );
    }

    fseek( fp, 0, SEEK_END );
    filelen = ftell( fp );
    rewind( fp );

    fread( &p->data, filelen, 1, fp );
    fclose( fp );

}

void _file_to_network_layer( packet *p )
{
    size_t datalen;
    FILE* fp = fopen( getenv( "OUTPUT_FILE" ), "wb" );

    if ( fp == NULL ) {
        fprintf( stderr , "error while writing to '%s'.\n", getenv( "OUTPUT_FILE" ) );
        exit( 1 );
    }

    datalen = strlen( p->data );

    fwrite( &p->data, datalen, 1, fp );
}


void _userio_from_network_layer( packet *p )
{
    printf( "Enter data to send : " );
    gets( p->data );
    fflush( stdin );
}

void _userio_to_network_layer( packet *p )
{
    printf( "Data recieved : %s\n", p->data );
}

void from_network_layer( packet *p )
{
    #ifdef DATA_FROM_FILE
    _file_from_network_layer( p );
    #else
    _userio_from_network_layer( p );
    #endif
}

void to_network_layer( packet *p )
{
    #ifdef DATA_FROM_FILE
    _file_to_network_layer( p );
    #else
    _userio_to_network_layer( p );
    #endif
}


#ifdef TESTING

int main( int argc, char *argv[] )
{
    packet p;

    from_network_layer( &p );

    to_network_layer( &p );

    printf( "\nProgram terminated successfully! Check the results..." );
}

#endif
