/**
 * The implementation of the Maximum Subarray Sum problem must
 * be done through "Divide-and-Conquer" strategy. You may refer
 * to Page Nos. (68 to 72) of the attached document for the same.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


/* Negative Infinity */
#define ninf INT_MIN


typedef struct {
    int lo;
    int hi;
    int sum;
} mssa; /* Maximum Sum Sub-Array (MSSA) */


/* Find Maximim Crossing Sub-Array (Find MCS) */
mssa _find_mcs( int *changes, int start, int mid, int end )
{
    int sum = 0;

    int leftsum = ninf,
        maxleft;

    for ( int i=mid ; i>=start ; i-- ) {
        sum += changes[i];
        if ( sum > leftsum ) {
            leftsum = sum;
            maxleft = i;
        }
    }

    sum = 0;

    int rightsum = ninf,
        maxright;

    for ( int i=mid+1 ; i<=end ; i++ ) {
        sum += changes[i];
        if ( sum > rightsum ) {
            rightsum = sum;
            maxright = i;
        }
    }

    mssa res = { maxleft, maxright, leftsum + rightsum };
    return res;
}


/* Solve Maximum Sum Sub-Array (Solve MSSA) */
mssa solve_mssa( int *changes, int start, int end )
{
    if ( start == end ) {
        mssa res = { start, end, changes[start] };
        return res;
    }

    int  mid      = (start + end) / 2;
    mssa leftsum  = solve_mssa( changes, start, mid );
    mssa rightsum = solve_mssa( changes, mid+1, end );
    mssa crosssum = _find_mcs( changes, start, mid, end );

    if      (  leftsum.sum > rightsum.sum &&  leftsum.sum > crosssum.sum ) return  leftsum;
    else if ( rightsum.sum >  leftsum.sum && rightsum.sum > crosssum.sum ) return rightsum;
    else                                                                   return crosssum;
}


int main( int argc, char *argv[] )
{
    int prices[] = {10, 11, 7, 10, 16};
    int N = 5;

    int *changes = ( int * ) malloc( (N-1) * sizeof( int ) );

    /* Find the changes */
    for ( int i=1 ;i<N ; i++ ) {
        changes[i-1] = prices[i] - prices[i-1];
    }

    mssa res = solve_mssa( changes, 0, N-2 );

    printf( " low  : %5d \n high : %5d \n", res.lo, res.hi+1 );
    printf( " sum  : %5d \n", res.sum );

    return 0;
}
