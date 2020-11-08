#include <stdio.h>
#include <stdlib.h>

#define swap( a,b,temp ) temp = a; \
                         a = b;    \
                         b = temp

/* Bubble sort Iterative */
void bsi( int *a, int n )
{
  int temp;

  for ( int i=0 ; i<n ; i++ ) {
    for ( int j=0 ; j<n-i-1 ; j++ ) {
      if ( a[j] > a[j+1] ) {
        swap( a[j], a[j+1], temp );
      }
    }
  }
}

/* Bubble sort Recursive */
void bsr( int *a, int k )
{
  if ( k==1 ) return;

  int temp;
  for( int j=0 ; j<k-1 ; j++ ) {
    if ( a[j] > a[j+1] ) {
      swap( a[j], a[j+1], temp );
    }
  }

  bsr( a, k-1 );
}

/* Selection sort iterative */
void ssi( int *a, int n )
{
  int minidx, temp;
  for ( int i=0 ; i<n ; i++ ) {
    minidx = i;
    for ( int j=i ; j<n; j++ ) {
      if( a[minidx] > a[j] ) minidx=j;
    }
    swap( a[minidx],a[i],temp );
  }
}

/* Selection sort recursive */
void ssr( int *a, int i, int n )
{
  if( i==n ) return;

  int minidx=i, temp;
  for( int j=i ; j<n; j++ ) {
    if( a[minidx] > a[j] ) minidx=j;
  }
  swap( a[minidx], a[i], temp );

  ssr( a , i+1 , n );
}

/* Insertion sort iterative */
void isi( int *a, int n )
{
  int
  key,
  i, j;

  for ( i=0 ; i<n ; i++ ) {
    key = a[i];
    j=i-1;
    while( j>=0 && a[j]>key ) {
      a[j+1] = a[j];
      j--;
    }
    a[j+1] = key; /* Insert key */
  }
}

/* Insertion sort recursive */
void isr( int *a, int i, int n )
{
  if ( i==n ) return;

  int key, j;
  key = a[i];
  j=i-1;
  while( j>=0 && a[j]>key ) {
    a[j+1] = a[j];
    j--;
  }
  a[j+1] = key; /* Insert key */

  isr( a, i+1, n );
}

int main( int argc, char *argv[] )
{
  int a[] = {766,747,825,74,785,192,8171,2,918};
  int *b  = ( int * ) malloc( 9 * sizeof( int ) );
  printf("Original Array                  : ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", a[i]);
  printf("\n");

  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  bsi( b,9 ); // Bubble Sort Iterative
  printf("Using BUbble Sort (Iterative)   : ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");

  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  bsr( b,9 ); // Bubble Sort Recursive
  printf("Using BUbble Sort (Recursive)   : ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");

  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  ssi( b,9 ); // Selection Sort Iterative
  printf("Using Selection Sort (Iterative): ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");


  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  ssr( b,0,9 ); // Selection Sort Recursive
  printf("Using Selection Sort (Recursive): ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");

  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  isi( b,9 ); // Insertion sort Iterative
  printf("Using Insertion sort (Iterative): ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");


  /* Copy a in b */
  for( int i=0 ; i<9; i++ ) b[i]=a[i];
  /* Run Sort */
  isr( b,0,9 ); // Insertion sort Recursive
  printf("Using Insertion sort (Recursive): ");
  for( int i=0 ; i<9 ; i++ ) printf("%d ", b[i]);
  printf("\n");

  free(b);

  return 0;
}
