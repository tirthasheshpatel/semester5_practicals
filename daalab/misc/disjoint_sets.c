#include <stdio.h>
#include <stdlib.h>

typedef enum {DOUBLE, FLOAT, INT} data_t;

typedef struct {
    void *owner;
    void *set;
} disjoint_set_node;

typedef struct {
    int size;
    data_t dtype;
    disjoint_set_node *set;
    void *(*comp_func)(void *, void *);
} disjoint_set;

void
makeset( disjoint_set *disjoint_set_obj,
         void *elements,
         data_t dtype,
         void *(*comp_func)(void *, void *) )
{
    disjoint_set_obj->dtype = dtype;
    disjoint_set_obj->comp_func = comp_func;


    disjoint_set_node *node = ( disjoint_set_node * ) malloc( sizeof( disjoint_set_node ) );
}

int main()
{
    return 0;
}
