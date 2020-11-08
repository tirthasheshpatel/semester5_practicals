#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap( int *a, int *b )
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

int _partition( int *a, int p, int r )
{
  /* Pivot */
  int x = a[r];

  /* Index where the swap will occur */
  int i = p-1;

  /* This is a "theta(n)" loop where "n=r-p" */
  for ( int j=p ; j<r ; j++ ) {
    /* If we find any element less than pivot, we exchange
       the next index element with this element. */
    if ( a[j] < x ) {
      i++;
      swap( &a[i], &a[j] );
    }
  }
  /* At last, we swap the pivot with the next index.
     This means that all the elements less than pivot
     are ahead of it and all the elements greater than it
     are behind it in the array. */
  swap( &a[i+1], &a[r] );

  return i+1;
}

int _randompartition( int *a, int p, int r )
{
  /* We take some random index i and swap with
     the last index... then we run normal
     quicksort algo. */
  int q = rand() % (r-p+1) + p;
  swap( &a[q], &a[r] );
  return _partition( a, p, r );
}

void quicksort( int *a, int p, int r )
{
  /* Recursion of the form :

     Worst case : T(n) =  T(n-1) + theta(n)
       - Worst case occurs when the array is sorted
         and the index "r" is incremented by one on
         each recursive call to partition function.
         Partition function takes theta(n) time
         to run for each call. OTOH, we are solving
         two subproblems of size "1" and "n-1".
         To solve the problem of size 1, we need only
         a constant time while to solve a problem of
         size n-1, we need "T(n-1)" time. Hence, the
         time complexity is :

                 T(n) = T(n-1) + T(1) + theta(n)
                 T(n) = T(n-1)        + theta(n)  ( T(1) is a constant absorbed in theta(n) )

     Best  case : T(n) = 2T(n/2) + theta(n)
       - This occurs when a uniformly distributed array
         is passed as argument. In this case, the partition
         function takes "theta(n)" time to run (on each
         recursive call) and the problem is devided into
         two subproblems of size "n/2" which are then solved
         recursively in time T(n/2). Hence, we get :

                 T(n) = 2T(n/2) + theta(n)

     Using Master Theorem, the complexity is derived as O( n lg n ).

     We can also use a tree to solve this recursion.

                            T(n)              =>    0 (Complexity: theta(n))
                           /    \
                      T(n/2)    T(n/2)        =>    1 (Complexity: theta(n))
                     /  \         /  \
               T(n/4) T(n/4) T(n/4) T(n/4)    =>    2 (Complexity: theta(n))
                 .      .      .      .
                 .      .      .      .
                 .      .      .      .
           T(1) T(1) T(1) T(1) ... T(1) T(1)  => lg n (Complexity: theta(n))

     Hence, we take time propotional to "theta(n) * height of the tree"
     to solve this problem which here is :

                            ---------------------
                            | theta( n * lg n ) | //
                            ---------------------//.
                                                //
   */
  if ( p<r ) {
    int q = _randompartition( a, p, r  );
    quicksort( a, p, q-1 );
    quicksort( a, q+1, r );
  }
}


int main( int argc, char *argv[] )
{
  int a[] = {23, 423, 343, 3452, 43, 4, 24, 3, 53, 4};

  printf("Original Array : ");
  for ( int i=0 ; i<10 ; i++ ) printf( "%d ", a[i] );
  printf("\nSorted   Array : ");
  quicksort(a, 0, 9);
  for ( int i=0 ; i<10 ; i++ ) printf( "%d ", a[i] );
  printf( "\n" );

  return 0;
}
