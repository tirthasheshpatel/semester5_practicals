#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>

#ifdef __unix
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#else
#error "A linux distribution is needed to run the code (WSL will also work)."
#endif

#include "protocol.h"

#define MAXBUF		1024
#define	MY_PORT		9998
#define PEER_PORT	9999
#define MAXIP		16		/* XXX.XXX.XXX.XXX */

char sbuffer[MAXBUF];
char rbuffer[MAXBUF];
int sd;


///////////////////////////////////////////////////////////////////
/////////////////////// PRIVATE INTERFACE /////////////////////////
///////////////////////////////////////////////////////////////////


/*--------------------------------------------------------------------*/
/* _set_address                                                       */
/*                                                                    */
/* Fill addr with info from XXX.XXX.XXX.XXX:XXXXX format.             */
/*--------------------------------------------------------------------*/
int _set_address(char* composite, struct sockaddr_in *addr)
{
	int i;
	char ip_address[MAXIP];

	bzero(addr, sizeof(*addr));
	addr->sin_family = AF_INET;
	for ( i = 0 ; composite[i] != ':' && composite[i] != 0  &&  i < MAXIP ; i++ ) ip_address[i] = composite[i];

	ip_address[i] = 0;

	if ( composite[i] == ':' ) addr->sin_port = htons(atoi(composite+i+1));
	else addr->sin_port = 0;

	if ( *ip_address == 0 ) {
		addr->sin_addr.s_addr = INADDR_ANY;
		return 0;
	}
	else return ( inet_aton(ip_address, &addr->sin_addr) == 0 );
}


/* configs : <my addr:port> <peer addr:port> */
int _setup( char *configs[] )
{
	struct sockaddr_in addr;

	if ( (sd = socket(PF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("Socket Error!");
		exit(errno);
	}

	if ( _set_address(configs[0], &addr) != 0 )
	{
		perror(configs[0]);
		exit(errno);
	}

	if ( bind(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 ) {
		perror("Bind Error!");
		exit(errno);
	}

	if ( _set_address(configs[1], &addr) != 0 ) {
		perror(configs[1]);
		exit(errno);
	}

	if ( connect(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0 ) {
		perror("Connect Error!");
		exit(errno);
	}

	printf( "\n\n\nCONNECTION ESTABLISHED [FD %d].\n\n\n", sd );

	return 0;
}

void _socket_from_physical_layer( frame *f, event_type *e )
{
    int bytes_read;

    bzero( rbuffer, sizeof( rbuffer ) );
    bytes_read = recv( sd, rbuffer, sizeof(rbuffer), 0 );
    while ( bytes_read <= 0 ) {
        if ( has_timedout() ) {
            printf("[DEBUG INFO] Timeout.\n");
            *e = TIMEOUT;
            return;
        }
        printf("[DEBUG INFO] Failed to read data. Trying again after 1 second...\n");
        sleep(1);
        bytes_read = recv( sd, rbuffer, sizeof(rbuffer), 0 );
    }

    *e = FRAME_ARRIVAL;

    printf("[DEBUG INFO] recieved buffer : %s\n", rbuffer);

    char
        frame_kind[] = { rbuffer[0], 0 },
        seq_number[] = { rbuffer[1], 0 },
        ack_number[] = { rbuffer[2], 0 },
        data[MAX_PKT];

    strcpy( data, rbuffer + 3 );

    printf("[DEBUG INFO] recieved ==> frame_kind : %s, seq : %s, ack : %s, data : %s\n", frame_kind, seq_number, ack_number, data);

    /* store the data into the frame */

    f->kind = atoi( frame_kind );
    f->seq  = atoi( seq_number );
    f->ack  = atoi( ack_number );
    strcpy( f->info.data, data );
}

void _socket_to_physical_layer( frame *f )
{
    /* encode frame to be sent */

    sprintf( sbuffer, "%d%d%d%s",
             f->kind, f->seq, f->ack, f->info.data );

    printf("[DEBUG INFO] sending buffer : %s\n", sbuffer);

    /* send data */

    if ( send( sd, sbuffer, strlen( sbuffer ), 0 ) == -1 ) {
        perror("error during sending data\n");
        exit(errno);
    }
}

void _pipe_from_physical_layer( frame *f )
{
    fprintf(stderr, "Pipe communication not implemented!\n");
    exit(0);
}

void _pipe_to_physical_layer( frame *f )
{
    fprintf(stderr, "Pipe communication not implemented!\n");
    exit(0);
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
/////////////////////// PUBLIC INTERFACE //////////////////////////
///////////////////////////////////////////////////////////////////

void establish_connection( char *peer1_addr, char *peer2_addr )
{
#ifdef USE_SOCKET
    char *configs[] = { peer1_addr, peer2_addr };
    _setup( configs );
#endif
}

void from_physical_layer( frame *f, event_type *e )
{
#ifdef USE_SOCKET
    _socket_from_physical_layer( f, e );
#else
    _pipe_from_physical_layer( f );
#endif
}

void to_physical_layer( frame *f )
{
#ifdef USE_SOCKET
    _socket_to_physical_layer( f );
#else
    _pipe_to_physical_layer( f );
#endif
}

void close_connection(  )
{
    close( sd );
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
