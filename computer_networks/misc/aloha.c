#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void simulate_aloha( double G, int t, int k )
{
    double success = 0;
    double x;
    int j;

    double *cdf = ( double * ) malloc( k * sizeof( double ) );

    for ( int i=0 ; i<k ; i++ )
        cdf[i] = exp( i*log(G) - G - lgamma(i+1) );

    for ( int i=1 ; i<k ; i++ )
        cdf[i] += cdf[i-1];

    printf( "sum of probabilities : %.6lf\n", cdf[k-1] );

    for ( int i=0 ; i<t ; i++ ) {
        x = drand48(), j = 0;
        while( j<k && x>cdf[j] ) j++;
        if( j==0 ) success++;
    }

    printf( "Mean     successes : %.8lf\n", success/t );
    printf( "Expected successes : %.8lf\n", exp( -G ) );
}

int main()
{
    srand( time(0) );
    simulate_aloha( 0.5, 100000, 200 );
}
