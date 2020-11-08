/**
 * AIM : Any 3 out of 4 operations on Binomial Heap.
 * 
 * This is the implementation of Binomial Heaps in C.
 * 
 * Operations implemented
 * ----------------------
 * 1. Union Binomial Heaps.
 * 2. Insert in Binomial Heap.
 * 3. Find the minimum element in the Binomial Heap.
 * 
 * Other operations implemented
 * ----------------------------
 * 1. Create a Binomial Heap.
 * 2. Print the Binomial Heap.
 * 
 * Notes
 * -----
 * There may be some memory leaks, I have not paid attention to.
 * 
 * Reference
 * ---------
 * .. [1] Implementation of Binomial Heap in C++ from
 *        https://www.geeksforgeeks.org/implementation-binomial-heap/
 * .. [2] Binomial Heap on Youtube
 *        https://youtu.be/7UQd9SYUoNk
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

/****************************************************************************/
/****************************** STURCTURES **********************************/
typedef struct _binom_tree_node {
    int key; /* Data in the node. */

    /* See [1]_ for the logic of using child, parent and a sibling */
    struct _binom_tree_node *child, *parent, *sibling; /* NOT MY LOGIC :-) */

    int k; /* Degree of the node. */
} binom_tree_node; /* (Private) Structure for a node in the tree. */

typedef struct _binom_heap_node {
    binom_tree_node *root;          /* Root of the heap. */
    struct _binom_heap_node *next;  /* Next node in the heap. */
} binom_heap_node; /* (Private) Structure for a node in the heap (which will be a binom_tree). */

typedef struct _binom_heap {
    binom_heap_node *trees;       /* Trees in the heap. */
    int size;                     /* Number of trees in the heap. */
} binom_heap; /* (Interface) Structure to the binomial heap. */
/****************************************************************************/


/****************************************************************************/
/*************************** PRIVATE FUNCTIONS ******************************/
binom_heap_node * _merge_binom_trees(binom_heap_node *a, binom_heap_node *b)
/**
 * Merges two trees present in a binomial heap node. As swapping occurs,
 * a pointer to the swapped node is returned.
*/
{
    if(a->root->key > b->root->key){
        binom_heap_node temp = *a;
        *a = *b;
        *b = temp;
    }

    b->root->parent = a->root;
    b->root->sibling = a->root->child;
    a->root->child = b->root;
    a->root->k++;

    return a;
}

void _fixup_binom_heap(binom_heap *c)
/**
 * Fix the binomial heap after mergeing.
 * This algorithm has been taken from [1]_ but
 * adopted for C.
*/
{
    if(c->size <= 1) return;

    binom_heap_node *curr = c->trees,
                    *next = c->trees->next,
                    *next_next = c->trees->next->next;

    while(curr) {

        if(next == NULL) curr = next;

        else if(curr->root->k < next->root->k) {
            curr = next;
            next = next_next;
            if(next_next) next_next = next_next->next;
        }

        else if(next_next &&
                curr->root->k == next->root->k &&
                curr->root->k == next_next->root->k) {
            curr = next;
            next = next_next;
            next_next = next_next->next;
        }

        else if(curr->root->k == next->root->k) {
            curr = _merge_binom_trees(curr, next);
            curr->next = next_next;
            free(next);
            next = next_next;
            if(next_next) next_next = next_next->next;
            c->size--;
        }

    }
}

void _print_binom_tree(binom_tree_node *root)
/**
 * Print a binomial tree using preorder traversal.
*/
{
    if(root) {
        printf("(key=%d, degree=%d) ", root->key, root->k);
        _print_binom_tree(root->child);
        _print_binom_tree(root->sibling);
    }
}
/****************************************************************************/


/****************************************************************************/
/*************************** INTERFACE FUNCTIONS ****************************/
void merge_binom_heaps(binom_heap *a, binom_heap *b, binom_heap *c)
{
    binom_heap_node *curr_a = a->trees,
                    *curr_b = b->trees;

    c->size = a->size + b->size;

    if(curr_a->root->k < curr_b->root->k) {
        c->trees = curr_a;
        curr_a = curr_a->next;
    }

    else {
        c->trees = curr_b;
        curr_b = curr_b->next;
    }

    binom_heap_node *curr_c = c->trees;

    while(curr_a && curr_b) {

        if(curr_a->root->k < curr_b->root->k) {
            curr_c->next = curr_a;
            curr_a = curr_a->next;
        }

        else {
            curr_c->next = curr_b;
            curr_b = curr_b->next;
        }

        curr_c = curr_c->next;

    }

    if      (curr_b) curr_c->next = curr_b;
    else if (curr_a) curr_c->next = curr_a;
}

void binom_heap_union(binom_heap *a, binom_heap *b, binom_heap *c)
{
    if(a == NULL || b == NULL || c == NULL) {
        fprintf(stderr, "[in 'binom_heap_union'] Heaps a, b, or c not initialized!\n");
        exit(1);
    }

    merge_binom_heaps(a, b, c);
    _fixup_binom_heap(c);
}

void binom_heap_create(binom_heap *heap, int key)
{
    if(heap == NULL) {
        fprintf(stderr, "[in 'binom_heap_create'] Heap not initialized!\n");
        exit(1);
    }

    heap->trees = (binom_heap_node *)malloc(sizeof(binom_heap_node));

    heap->trees->root = (binom_tree_node *)malloc(sizeof(binom_tree_node));
    heap->trees->root->key = key, heap->trees->root->k = 0;
    heap->trees->root->child = heap->trees->root->parent = heap->trees->root->sibling = NULL;
    heap->trees->next = NULL;

    heap->size = 1;
}

void binom_heap_insert(binom_heap *heap, int key)
{
    binom_heap *new_heap = (binom_heap *)malloc(sizeof(binom_heap));
    binom_heap_create(new_heap, key);

    binom_heap *merged_heap = (binom_heap *)malloc(sizeof(binom_heap));
    binom_heap_union(heap, new_heap, merged_heap);
    *heap = *merged_heap;
    free(new_heap);
    free(merged_heap);
}

int binom_heap_find_min(binom_heap *heap)
{
    binom_heap_node *temp = heap->trees;
    binom_heap_node *min_node = temp;

    while(temp) {
        if(min_node->root->key > temp->root->key) min_node = temp;
        temp = temp->next;
    }

    return min_node->root->key;
}

void binom_heap_print(binom_heap *heap)
{
    int i = 0;
    printf("Binomial Heap of size : %d\n", heap->size);
    for(binom_heap_node *temp=heap->trees; temp; temp=temp->next, i++) {
        printf("%d'th binomial tree : ", i);
        _print_binom_tree(temp->root);
        printf("\n");
    }
}
/****************************************************************************/

/****************************************************************************/
/****************************** DRIVER FUNCTION *****************************/
int main( int argc, char *argv[] )
{
    binom_heap a;

    /* Create a binomial heap. */
    binom_heap_create(&a, 0);

    /* Insert values in the heap. */
    binom_heap_insert(&a, 1);
    binom_heap_insert(&a, 2);
    binom_heap_insert(&a, 3);
    binom_heap_insert(&a, 4);
    binom_heap_insert(&a, 5);
    binom_heap_insert(&a, -6);
    binom_heap_print(&a);

    /* Find the minimum key. */
    printf("Minimum key : %d\n", binom_heap_find_min(&a));

    return 0;
}
/****************************************************************************/
