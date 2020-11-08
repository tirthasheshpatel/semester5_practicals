#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INDEX(a,i,j,lda)  a[ (i)*lda + (j) ]
#define m(i, j)           m[ (i)*(w+1) + (j) ]
#define max(a, b)         (((a) < (b)) ? (a) : (b))

void printm(int *a, int lda, int m, int n)
{
    printf("/ ");
    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" \\\n");
    for (int i=0 ; i<m ; i++) {
        printf("| ");
        for (int j=0 ; j<n ; j++) {
            printf("%5d ", INDEX(a,i,j,lda));
        }
        printf(" |\n");
    }
    printf("\\ ");
    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" /\n");
}

int knapsack01(int w, int *weights, int *value, int n)
{
    int *m = (int *) malloc( (n+1)*(w+1) * sizeof(int) );

    for(int i=0; i<w+1; i++) m(0, i) = 0;
    for(int j=0; j<n+1; j++) m(j, 0) = 0;

    for(int n_items=1; n_items<n+1; n_items++) {
        for(int weight=1; weight<w+1; weight++) {
            if ( weights[ n_items-1 ] <= weight ) {
                m( n_items , weight ) = max(
                    value[ n_items-1 ] + m( n_items-1 , weight - weights[ n_items-1 ] ) ,
                    m( n_items-1 , weight )
                );
            }
            else {
                m( n_items , weight ) = m( n_items-1 , weight );
            }
        }
    }

    int max_rev = m( n, w );

    printm(m, w+1, n+1, w+1);

    free(m);

    return max_rev;
}


int main()
{
    int w = 100;
    int weights[] = {10, 20, 30, 40, 60};
    int value[]   = {1,  4,  5,  10, 8 };

    printf("Maximum revenue possible : %d\n", knapsack01(w, weights, value, 5));
    return 0;
}