#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

typedef struct
{
    void **objs;

    size_t count;
    size_t bufferSize;
} Vector;


Vector * vector_init();
Vector * vector_create(void **objs, size_t count);
void vector_append(Vector *v, void *obj);

void vector_sort(Vector *v, int (*compar)(const void*,const void*));

#endif
