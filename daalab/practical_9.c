#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define m(i,j) m[ (i)*n + (j) ]
#define s(i,j) s[ (i)*n + (j) ]

typedef struct {
    int nmuls;
    int *chain;
    int *memo;
} matrix_chain_mutiply_t;

matrix_chain_mutiply_t matrix_chain_multiply(int *a, int n)
{
    int *m = (int *) malloc( n*n * sizeof(int) );
    int *s = (int *) malloc( n*n * sizeof(int) );
    int q, minq, idx = -1;

    for(int i=0 ; i<n ; i++) m(i,i) = 0;

    for(int l=1 ; l<n ; l++) {
        for(int i=0 ; i<n-l ; i++) {
            int j = i+l;
            minq = INT_MAX;
            for(int k=i ; k<j ; k++) {
                q = m(i,k) + m(k+1, j) + a[i]*a[k+1]*a[j+1];
                if (q < minq) {
                    minq = q;
                    idx  = k;
                }
            }
            s(i,j) = idx;
            m(i,j) = minq;
        }
    }

    minq = m(0,n-1);

    matrix_chain_mutiply_t sol = {minq, s, m};
    return sol;
}

void _printc(int *s, int i, int j, int n)
{
    if ( i == j ) {
        printf(".");
        return;
    }
    printf("(");
    _printc(s,        i, s(i,j), n);
    _printc(s, s(i,j)+1,      j, n);
    printf(")");
}

void printc(int *s, int n)
{
    _printc(s, 0, n-1, n);
    printf("\n");
}

void printm(int *s, int n)
{
    printf("/ ");
    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" \\\n");
    for (int i=0 ; i<n ; i++) {
        printf("| ");
        for (int j=0 ; j<n ; j++) {
            printf("%5d ", s(i,j));
        }
        printf(" |\n");
    }
    printf("\\ ");
    for( int i=0 ; i<n ; i++ ) printf("      ");
    printf(" /\n");
}


int main()
{
    int shapes[] = {2, 3, 5, 2, 4, 3};
    matrix_chain_mutiply_t sol = matrix_chain_multiply(shapes, 5);
    printf("Minimum number of multiplications : %d\n", sol.nmuls);
    printf("Parenthesization : ");
    printc(sol.chain, 5);
    printf("m = \n");
    printm(sol.memo, 5);
    printf("s = \n");
    printm(sol.chain, 5);
    free(sol.chain);
    free(sol.memo);
    return 0;
}

