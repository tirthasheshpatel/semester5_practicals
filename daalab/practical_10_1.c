#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/* used by printm routine */
#define INDEX(a,i,j,lda)  a[ (i)*lda + (j) ]
#define INDENT(n)         for(int _ = 0; _ < n ; _++) printf(" ")

/* used by knapsack01 routine */
#define M(i, j)           M[ (i)*(w+1) + (j) ]
#define max(a, b)         (((a) > (b)) ? (a) : (b))

void printm(const char *name,
            const int *a,
            const int lda,
            const int m,
            const int n)
{
    const int len = strlen(name) + 1;
    const int mid = m / 2;

    INDENT(len);
    printf("/ ");

    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" \\\n");
    for (int i=0 ; i<m ; i++) {
        if ( i == mid ) printf("%s ", name);
        else INDENT(len);
        printf("| ");
        for (int j=0 ; j<n ; j++) {
            printf("%5d ", INDEX(a,i,j,lda));
        }
        printf(" |\n");
    }
    INDENT(len);
    printf("\\ ");
    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" /\n");
}

int knapsack01(const int w,
               const int *weights,
               const int *value,
               const int n)
{
    int *M = ( int * ) malloc( (n+1)*(w+1) * sizeof(int) );

    for(int i = 0 ; i < w+1 ; i++) M(0, i) = 0;
    for(int j = 0 ; j < n+1 ; j++) M(j, 0) = 0;

    for ( int n_items = 1 ; n_items < n+1 ; n_items++ ) {
        for (int weight = 1 ; weight < w+1 ; weight++ ) {
            if ( weights[ n_items-1 ] <= weight ) {
                M( n_items , weight ) = max(
                    value[ n_items-1 ] + M( n_items-1 , weight - weights[ n_items-1 ] ) ,
                    M( n_items-1 , weight )
                );
            }
            else {
                M( n_items , weight ) = M( n_items-1 , weight );
            }
        }
    }

    int max_loot = M( n, w );

    printm("Memoization Table Entries ==> ", M, w+1, n+1, w+1);

    free(M);

    return max_loot;
}


int main()
{
    int n = 4, w = 16;
    int weights[] = {5, 6, 7, 8};
    int value[]   = {10, 15, 60, 45};

    printf("\n\tMaximum loot possible : %d\n\n", knapsack01(w, weights, value, n));
    return 0;
}
