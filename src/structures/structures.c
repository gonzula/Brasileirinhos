#include <stdlib.h>

#include "structures.h"

Vector * vector_from_list(List *aList)
{
    Vector *v = vector_init();
    LIST_LOOP(aList)
    {
        vector_append(v, node->object);
    }
    return v;
}

List *
list_from_vector(Vector * v)
{
    List *l = list_init();
    for (int i = 0; i < v->count; i++)
    {
        list_append(l, v->objs[i]);
    }
    return l;
}
