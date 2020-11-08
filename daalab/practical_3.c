/**
 * Consider a file containing 500 integers as an input.
 * From this file, fetch 50 integers at a time and copy them in a sorted (ascending) order.
 * Repeat the same process for next 50 integers and merge them with previously sorted 50
 * integers, and hence form the sorted sequence of 100 integers.
 * Expected Output:- The output file must contain all 500 integers in a sorted(ascending) order. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int
comp( const void *a, const void *b )
{
    return ( *( int * )a - *( int * )b );
}

void
merge( int *a, int n, int *b, int m, int *c )
{
    int i=0, j=0, k=0;

    while ( i<n && j<m ) {
        if ( a[i] < b[j] ) {
            c[k] = a[i];
            k++;
            i++;
        }
        else {
            c[k] = b[j];
            k++;
            j++;
        }
    }

    while ( i<n ) {
        c[k] = a[i];
        k++;
        i++;
    }

    while ( j<m ) {
        c[k] = b[j];
        k++;
        j++;
    }
}


void
run( char *file_name, char *output )
{
    printf("Running...\n");

    char
    ch,
    *buffer = ( char * ) malloc ( 10 * sizeof( char ) );

    int
    *a = ( int * ) malloc (  50 * sizeof( int ) ), /* this array stores the current batch */
    *b = ( int * ) malloc ( 500 * sizeof( int ) ), /* this array stores all previous batches */
    *c = ( int * ) malloc ( 500 * sizeof( int ) ), /* this array stores all the batches in sorted order */
    i = 0, j = 0, batch = 0, tmp;

    FILE
    *fp = fopen( file_name, "r" );

    if (fp == NULL) {
        perror( "Error while opening the file.\n" );
        exit( EXIT_FAILURE );
    }

    while((ch = fgetc(fp)) != EOF) {
        if ( isspace( ch ) ) {
            buffer[i] = '\0';
            i = 0;

            tmp = atoi( buffer );

            a[j++] = tmp;

            if ( j == 50 ) {
                qsort( a, 50, sizeof( int ), comp ); /* sort the current batch */

                if ( batch == 0 ) {
                    /* update both b and c to coresspond with a */
                    for ( j=0 ; j<50 ; j++ ) b[j] = a[j];
                    for ( j=0 ; j<50 ; j++ ) printf("%d ", b[j]);
                    printf("\n\n");
                }
                else if ( batch >= 1 ) {
                    /* merge a with the array b and put the result in c */
                    merge( a, 50, b, 50*batch, c );
                    /* now empty all the sorted elements back in b from c */
                    for ( j=0 ; j<50*(batch+1) ; j++ ) b[j] = c[j];
                    for ( j=0 ; j<50*(batch+1) ; j++ ) printf("%d ", b[j]);
                    printf("\n\n");
                }

                batch++; /* increase batch number */
                j = 0;   /* set the index to 0. */
            }
        }
        else {
            buffer[i] = ch;
            i++;
        }
    }

    free( buffer );
    free( a );
    free( b );

    fclose( fp );

    fp = fopen( output, "w" );

    for ( i=0 ; i<500 ; i++ ) {
        fprintf( fp, "%d ", c[i] );
    }

    free( c );

    fclose( fp );
}


void
generate( char *file_name )
{
    printf("Generating...\n");

    srand( time(0) );

    FILE
    *fp = fopen(file_name, "w");

    if (fp == NULL) {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    for ( int i=0 ; i<500 ; i++ ) {
        fprintf( fp, "%d ", rand() % 100 );
    }

    fclose( fp );
}


int main( int argc, char *argv[] )
{
    generate( "read.txt" );
    run( "read.txt", "write.txt" );
    printf("Finished!\n");

    return 0;
}
