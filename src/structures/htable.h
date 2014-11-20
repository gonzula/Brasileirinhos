#ifndef structures_htable_h
#define structures_htable_h

#include "refcnt.h"

// #define HTABLE_LOOP(_t) for (int _i = 0, int _j = 0; _j < _t->count; i++)

typedef unsigned long Hash;

typedef struct
{
    char *key;
    void *obj;
} Entry;

typedef struct _tableBucket
{
    Entry *entry;
    struct _tableBucket *next;

} TableBucket;

typedef struct
{
    TableBucket **table;
    size_t count;
} HashTable;


HashTable * htable_init();
HashTable * htable_set(HashTable * t, char *key, void *obj);
void * htable_retrieve(HashTable *t, const char *key, int remove);
void * htable_retrieve_by_value(HashTable *t, int value);
void htable_iterate(HashTable *t, void *context, void (*obj_iteration)(Entry *entry, int i, int count, int *stop, void *context));
Hash string_hash(const char *string);


#endif
