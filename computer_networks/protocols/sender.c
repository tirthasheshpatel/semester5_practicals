#include <stdio.h>
#include "protocol.h"

int main( int argc, char *argv[] )
{
    int count = 7;

    if ( argc != 3 ) {
        fprintf( stderr, "usage: ./protocol5 <peer_1_address> <peer_2_address>\n" );
        fprintf( stderr, "If you are using the source code, please use the make file to compile the program\n" );
        fprintf( stderr, "Use this command : 'make sender'\n" );
        fprintf( stderr, "This will compile all the necessary programs and start executing the main program!\n" );
        exit(0);
    }

    seq_nr next_frame_to_send;       /* 0 or 1 only */
    seq_nr frame_expected;           /* 0 or 1 only */
    frame r, s;                      /* scratch variables */
    packet buffer;                   /* current packet being sent */
    event_type event;

    establish_connection( argv[1], argv[2] );

    next_frame_to_send = 0;
    frame_expected = 0;
    from_network_layer( &buffer );   /* fetch a packet from the network layer */
    s.info = buffer;                 /* prepare to send the initial frame */
    s.seq  = next_frame_to_send;     /* insert sequence number into frame */
    s.ack  = 1 - frame_expected;     /* piggybacked ack */
    to_physical_layer( &s );         /* transmit the frame */
    start_timer( &s.seq );           /* start the timer running */

    while( count-- ) {
        from_physical_layer( &r, &event );

        if ( event == FRAME_ARRIVAL ) {
            if ( r.seq == frame_expected ) {
                to_network_layer( &r.info );
                INC(frame_expected);
            }

            if ( r.ack == next_frame_to_send ) {
                stop_timer( &r.ack );
                printf("[DEBUG INFO] Sending another message\n");
                from_network_layer( &buffer );
                INC( next_frame_to_send );
            }
        }

        s.info = buffer;
        s.seq = next_frame_to_send;
        s.ack = 1 - frame_expected;
        to_physical_layer( &s );
        start_timer( &s.seq );
    }

    stop_timer( 0 );
    close_connection(  );

    return 0;
}
