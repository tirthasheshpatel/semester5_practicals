#ifndef GUARD_PROTOCOL_H
#define GUARD_PROTOCOL_H

#define MAX_PKT 1024
#define MAX_SEQ 1

typedef enum {FALSE, TRUE} boolean;
typedef unsigned int seq_nr;
typedef struct {unsigned char data[MAX_PKT];} packet;
typedef enum {DATA, ACK, NACK} frame_kind;
typedef enum {FRAME_ARRIVAL, TIMEOUT} event_type;

typedef struct {
    frame_kind kind;
    seq_nr seq;
    seq_nr ack;
    packet info;
} frame;

#define INC( k ) if ( k<MAX_SEQ ) k++ ; else k=0
#define USE_SOCKET

/* Check if the clock has timed out. */
int has_timedout(  );

/* Fetch a packet from the network layer for transmission on the channel. */
void from_network_layer( packet * );

/* Deliver information from an inbound frame to the network layer. */
void to_network_layer( packet * );

/* Go get an inbound frame from the physical layer and copy it to r. */
void from_physical_layer( frame *, event_type * );

/* Pass the frame to the physical layer for transmission. */
void to_physical_layer( frame * );

/* establishes connection between two peers. */
void establish_connection( char *, char * );

/* close a connection */
void close_connection(  );

/* Start the clock running and enable the timeout event. */
void start_timer( seq_nr * );

/* Stop the clock and disable the timeout event. */
void stop_timer( seq_nr * );

#endif