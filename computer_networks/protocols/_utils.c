#include "protocol.h"
#ifdef __unix
#include <signal.h>
#include <unistd.h>
#else
#error "A linux distribution is needed to run the code (WSL will also work)."
#endif

struct sigaction sact;

int timeout = 0;

void _sigalrm_handler( int sig )
{
    timeout = 1;
}

void start_timer( seq_nr *seq )
{
    sigemptyset( &sact.sa_mask );
    sact.sa_flags = 0;
    sact.sa_handler = _sigalrm_handler;
    sigaction( SIGALRM, &sact, NULL );

    timeout = 0;

    alarm( 10 );
}

void stop_timer( seq_nr *seq )
{
    alarm( 0 );
    timeout = 0;
}

int has_timedout(  )
{
    return ( timeout == 1 );
}
