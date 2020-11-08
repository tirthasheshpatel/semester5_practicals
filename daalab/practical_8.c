#include <stdio.h>
#include <stdlib.h>

#define  INDEX(  a,i,j,lda )  a[  (i)*lda + (j) ]
#define  POINT(  a,i,j,lda )  a + (i)*lda + (j)

#define  MATRIX( m,n )  ( int * ) calloc ( m*n , sizeof(int) )


void add(int *a, int lda, int *b, int ldb, int *c, int ldc, int n)
{
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<n ; j++) {
            INDEX(c,i,j,ldc) = INDEX(a,i,j,lda) + INDEX(b,i,j,ldb);
        }
    }
}


void sub(int *a, int lda, int *b, int ldb, int *c, int ldc, int n)
{
    for (int i=0 ; i<n ; i++) {
        for (int j=0 ; j<n ; j++) {
            INDEX(c,i,j,ldc) = INDEX(a,i,j,lda) - INDEX(b,i,j,ldb);
        }
    }
}


void strassen(int *a, int lda, int *b, int ldb, int *c, int ldc, int n)
{
    if (n == 1) {
        c[0] = a[0]*b[0];
        return;
    }

    int s = n/2;

    int *s1  =  MATRIX(s,s);
    int *s2  =  MATRIX(s,s);
    int *s3  =  MATRIX(s,s);
    int *s4  =  MATRIX(s,s);
    int *s5  =  MATRIX(s,s);
    int *s6  =  MATRIX(s,s);
    int *s7  =  MATRIX(s,s);
    int *s8  =  MATRIX(s,s);
    int *s9  =  MATRIX(s,s);
    int *s10 =  MATRIX(s,s);

    int *p1  =  MATRIX(s,s);
    int *p2  =  MATRIX(s,s);
    int *p3  =  MATRIX(s,s);
    int *p4  =  MATRIX(s,s);
    int *p5  =  MATRIX(s,s);
    int *p6  =  MATRIX(s,s);
    int *p7  =  MATRIX(s,s);

    sub(POINT(b,0,s,ldb), ldb, POINT(b,s,s,ldb), ldb,  s1, s, s);
    add(POINT(a,0,0,lda), lda, POINT(a,0,s,lda), lda,  s2, s, s);
    add(POINT(a,s,0,lda), lda, POINT(a,s,s,lda), lda,  s3, s, s);
    sub(POINT(b,s,0,ldb), ldb, POINT(b,0,0,ldb), ldb,  s4, s, s);
    add(POINT(a,0,0,lda), lda, POINT(a,s,s,lda), lda,  s5, s, s);
    add(POINT(b,0,0,ldb), ldb, POINT(b,s,s,ldb), ldb,  s6, s, s);
    sub(POINT(a,0,s,lda), lda, POINT(a,s,s,lda), lda,  s7, s, s);
    add(POINT(b,s,0,ldb), ldb, POINT(b,s,s,ldb), ldb,  s8, s, s);
    sub(POINT(a,0,0,lda), lda, POINT(a,s,0,lda), lda,  s9, s, s);
    add(POINT(b,0,0,ldb), ldb, POINT(b,0,s,ldb), ldb, s10, s, s);

    strassen(POINT(a,0,0,lda), lda,                s1,   s, p1, s, s);
    strassen(              s2,   s,  POINT(b,s,s,ldb), ldb, p2, s, s);
    strassen(              s3,   s,  POINT(b,0,0,ldb), ldb, p3, s, s);
    strassen(POINT(a,s,s,lda), lda,                s4,   s, p4, s, s);
    strassen(              s5,   s,                s6,   s, p5, s, s);
    strassen(              s7,   s,                s8,   s, p6, s, s);
    strassen(              s9,   s,               s10,   s, p7, s, s);

    free( s1);
    free( s2);
    free( s3);
    free( s4);
    free( s5);
    free( s6);
    free( s7);
    free( s8);
    free( s9);
    free(s10);

    add(POINT(c,0,0,ldc), ldc, p5, s, POINT(c,0,0,ldc), ldc, s);
    add(POINT(c,0,0,ldc), ldc, p4, s, POINT(c,0,0,ldc), ldc, s);
    sub(POINT(c,0,0,ldc), ldc, p2, s, POINT(c,0,0,ldc), ldc, s);
    add(POINT(c,0,0,ldc), ldc, p6, s, POINT(c,0,0,ldc), ldc, s);

    add(POINT(c,0,s,ldc), ldc, p1, s, POINT(c,0,s,ldc), ldc, s);
    add(POINT(c,0,s,ldc), ldc, p2, s, POINT(c,0,s,ldc), ldc, s);

    add(POINT(c,s,0,ldc), ldc, p3, s, POINT(c,s,0,ldc), ldc, s);
    add(POINT(c,s,0,ldc), ldc, p4, s, POINT(c,s,0,ldc), ldc, s);

    add(POINT(c,s,s,ldc), ldc, p5, s, POINT(c,s,s,ldc), ldc, s);
    add(POINT(c,s,s,ldc), ldc, p1, s, POINT(c,s,s,ldc), ldc, s);
    sub(POINT(c,s,s,ldc), ldc, p3, s, POINT(c,s,s,ldc), ldc, s);
    sub(POINT(c,s,s,ldc), ldc, p7, s, POINT(c,s,s,ldc), ldc, s);

    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(p5);
    free(p6);
    free(p7);
}


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


int main()
{
    int n = 8;
    int A[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };

    int k=0;
    for(int i=0 ; i<n ; i++)
        for(int j=0 ; j<n ; j++)
            INDEX(A,i,j,n) = ++k;

    int B[] = {
        1, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1,
    };
    int C[] = {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
    };
    strassen(A, n, B, n, C, n, n);
    printm(C, n, n, n);
    return 0;
}
