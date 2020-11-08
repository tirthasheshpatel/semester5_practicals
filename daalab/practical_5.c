#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>


#define inf INT_MAX
#define MAX_SIZE 100
// #define DEBUG_MODE
#define graph( i,j ) graph[ (i)*n + (j) ]


/* adjecency list representation for Graphs */
typedef struct {
    int weight[MAX_SIZE];
    int adj[MAX_SIZE];
    int adj_size;
} adj_list_node;


void print_mst_adj_list( adj_list_node *graph, int *mst, const int n )
{
    printf("Edges in the MST.\n\n");
    for ( int i=1 ; i<n ; i++ ) {
        printf("   %-5d - %5d   \n", mst[i], i );
    }
}


void print_mst_adj_matrix( int *graph, int *mst, const int n )
{
    printf("Edges in the MST.\n\n");
    for ( int i=1 ; i<n ; i++ ) {
        printf("   %-5d - %5d   ===>   %5d   \n", mst[i], i, graph( i, mst[i] ) );
    }
}


void prim_adj_list( adj_list_node *graph, int *mst, const int n )
{
    bool *visited = ( bool * ) calloc ( n , sizeof( bool ) );
    int  *key     = ( int  * ) malloc ( n * sizeof( int  ) );

    /* 'key' values of all the vertices will initially be 'inf' */
    for ( int i=0 ; i < n ; i++ ) key[i] = inf;

    key[0] = 0;  /* Start with vertex 0. */
    mst[0] = -1; /* No parent of the first vertex. */

    for ( int count=0 ; count < n-1 ; count++ ) {

        /* Find minimum key and include it in visited array. */
        int min_key = inf;
        int u = -1; /* Vertex corresponding to the minimum key. */
        for ( int i=0 ; i < n ; i++ ) {
            if ( key[i] < min_key && visited[i] == false ) {
                min_key = key[i];
                u = i;
            }
        }

        visited[u] = true; /* Mark 'u' as visited. */

        /* If debugging is on, print the vertex found with minimum key. */
        #ifdef DEBUG_MODE
        printf("[INFO] found min key : %d\n", u);
        #endif

        /* Iterate throught all the edges of the node 'u'. */
        for ( int j=0 ; j < graph[u].adj_size ; j++ ) {
            int v      = graph[u].adj[j];
            int weight = graph[u].weight[j];

            /* If debugging is on, print the edge being explored. */
            #ifdef DEBUG_MODE
            printf("[INFO] At vertex %d from %d with weight %d\n", v, u, weight);
            #endif

            if ( visited[v] == false && weight < key[v] ) {
                mst[v] = u;
                key[v] = weight;

                /* If debugging is on, print the included edge. */
                #ifdef DEBUG_MODE
                printf("[INFO] Vertex %d from %d with weight %d inserted in MST\n", v, u, weight);
                #endif
            }
        }
    }

    free( visited );
    free( key );
}

void prim_adj_matrix( int *graph, int *mst, const int n )
{
    bool *visited = ( bool * ) calloc ( n , sizeof( bool ) );
    int  *key     = ( int  * ) malloc ( n * sizeof( int  ) );

    /* 'key' values of all the vertices will initially be 'inf' */
    for ( int i=0 ; i < n ; i++ ) key[i] = inf;

    key[0] = 0;  /* Start with vertex 0. */
    mst[0] = -1; /* No parent of the first vertex. */

    for ( int count=0 ; count < n-1 ; count++ ) {

        /* Find minimum key and include it in visited array. */
        int min_key = inf;
        int u = -1; /* Vertex corresponding to the minimum key. */
        for ( int i=0 ; i < n ; i++ ) {
            if ( key[i] < min_key && visited[i] == false ) {
                min_key = key[i];
                u = i;
            }
        }

        visited[u] = true; /* Mark 'u' as visited. */

        /* If debugging is on, print the vertex found with minimum key. */
        #ifdef DEBUG_MODE
        printf( "[INFO] found min key : %d\n", u );
        #endif

        /* Iterate throught all the edges of the node 'u'. */
        for ( int v=0 ; v < n ; v++ ) {
            /* If debugging is on, print the edge being explored. */
            #ifdef DEBUG_MODE
            printf( "[INFO] At vertex %d from %d with weight %d\n", v, u, graph( u, v ) );
            #endif

            if ( graph( u, v ) && visited[v] == false && graph( u, v ) < key[v] ) {
                mst[v] = u;
                key[v] = graph( u, v );

                /* If debugging is on, print the included edge. */
                #ifdef DEBUG_MODE
                printf( "[INFO] Vertex %d from %d with weight %d inserted in MST\n", v, u, graph( u, v ) );
                #endif
            }
        }
    }

    free( visited );
    free( key );
}


int main( int argc, char *argv[] )
{
    const int n = 8;

    printf("Running prim's algorithm\n");

    int *mst = ( int * ) malloc ( sizeof( int ) * n );
    adj_list_node *graph = ( adj_list_node * ) malloc ( sizeof( adj_list_node ) * n );

    graph[0].adj[0] = 3;
    graph[0].adj[1] = 1;
    graph[0].adj[2] = 4;
    graph[0].weight[0] = 1;
    graph[0].weight[1] = 2;
    graph[0].weight[2] = 5;
    graph[0].adj_size = 3;

    graph[1].adj[0] = 0;
    graph[1].adj[1] = 2;
    graph[1].adj[2] = 5;
    graph[1].adj[3] = 6;
    graph[1].weight[0] = 2;
    graph[1].weight[1] = 9;
    graph[1].weight[2] = 9;
    graph[1].weight[3] = 9;
    graph[1].adj_size = 4;

    graph[2].adj[0] = 1;
    graph[2].adj[1] = 5;
    graph[2].adj[2] = 4;
    graph[2].weight[0] = 9;
    graph[2].weight[1] = 7;
    graph[2].weight[2] = 1;
    graph[2].adj_size = 3;

    graph[3].adj[0] = 0;
    graph[3].weight[0] = 1;
    graph[3].adj_size = 1;

    graph[4].adj[0] = 0;
    graph[4].adj[1] = 2;
    graph[4].weight[0] = 5;
    graph[4].weight[1] = 1;
    graph[4].adj_size = 2;

    graph[5].adj[0] = 1;
    graph[5].adj[1] = 2;
    graph[5].adj[2] = 6;
    graph[5].adj[3] = 7;
    graph[5].weight[0] = 9;
    graph[5].weight[1] = 7;
    graph[5].weight[2] = 1;
    graph[5].weight[3] = 7;
    graph[5].adj_size = 4;

    graph[6].adj[0] = 1;
    graph[6].adj[1] = 5;
    graph[6].adj[2] = 7;
    graph[6].weight[0] = 9;
    graph[6].weight[1] = 1;
    graph[6].weight[2] = 2;
    graph[6].adj_size = 3;

    graph[7].adj[0] = 5;
    graph[7].adj[1] = 6;
    graph[7].weight[0] = 7;
    graph[7].weight[1] = 2;
    graph[7].adj_size = 2;

    prim_adj_list( graph, mst, n );
    printf("\n==== MST FOUND ====\n\n");
    print_mst_adj_list( graph, mst, n );
    printf("\n\n");

    free( graph );
    free( mst );

    int graph_[25] = {  0, 2, 0, 6, 0,
                        2, 0, 3, 8, 5,
                        0, 3, 0, 0, 7,
                        6, 8, 0, 0, 9,
                        0, 5, 7, 9, 0  };

    prim_adj_matrix( graph_, mst, 5 );
    printf("\n==== MST FOUND ====\n\n");
    print_mst_adj_matrix( graph_, mst, 5 );

    return 0;
}
