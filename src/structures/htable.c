#include <stdlib.h>
#include <string.h>
#include "htable.h"

#define TABLE_SIZE (1 << 10)
#define streq(a, b) (strcmp(a,b)==0)

Entry * entry_create(char *key, void *obj);
void entry_free(Entry *e);
Hash string_hash(const char * string);

void
_htable_release(void *t);

HashTable *
htable_init()
{
    HashTable * t = (HashTable *)alloc(sizeof(HashTable), _htable_release);
    t->table = (TableBucket**)calloc(TABLE_SIZE, sizeof(TableBucket*));
    t->count = 0;
    return t;
}


HashTable *
htable_set(HashTable * t, char *key, void *obj)
{
    Entry * e = entry_create(key, obj);
    Hash hash = string_hash(key);
    TableBucket * bucket = *(t->table + (hash & (TABLE_SIZE - 1))); /* acha bucket */
    TableBucket * pBucket = NULL; /* previousBucket */
    while (bucket && !streq(bucket->entry->key, key)) /* se ouver colisão ou chave já existia na tabela */
    {
        pBucket = bucket;
        bucket = bucket->next; /* avança até o ultimo bucket da lista */
    }
    if (!bucket)  /* nova Entry */
    {
        bucket = (TableBucket*)malloc(sizeof(TableBucket));
        bucket->next = NULL;
        bucket->entry = NULL;
        t->count++;
    }
    else      /* atualização de Entry */
    {
        entry_free(bucket->entry);
        bucket->entry = NULL;
    }

    if (pBucket)
    {
        pBucket->next = bucket;
    }

    bucket->entry = e;

    if (!t->table[hash & (TABLE_SIZE - 1)])
    {
        t->table[hash & (TABLE_SIZE - 1)] = bucket;
    }

    return t;
}

void *
htable_retrieve(HashTable *t, const char * key, int remove)
{
    Hash hash = string_hash(key);
    TableBucket ** tBucket = &t->table[hash & (TABLE_SIZE - 1)];
    TableBucket * bucket = *tBucket;
    TableBucket * pBucket = NULL;
    while (bucket && !streq(bucket->entry->key, key))
    {
        pBucket = bucket;
        bucket = bucket->next;
    }
    if (bucket)  /* se encontrou Entry */
    {
        Entry *entry = bucket->entry;
        void *obj = entry->obj;
        if (remove)
        {
            if (pBucket)
            {
                pBucket->next = bucket->next;
            }
            else
            {
                *tBucket = bucket->next;
            }
            free(bucket);
            retain(entry->obj);
            entry_free(entry);
            t->count--;
        }
        return obj;
    }
    return NULL; /* se não encontrou */
}

void
htable_iterate(HashTable *t, void *context, void (*obj_iteration)(Entry *entry, int i, int count, int *stop, void *context))
{
    int stop = 0;
    for (int i = 0, j = 0; j < t->count && !stop; i++)
    {
        if (t->table[i])
        {
            TableBucket * bucket = t->table[i];
            while (bucket && !stop)
            {
                obj_iteration(bucket->entry, j, t->count, &stop, context);
                j++;
                bucket = bucket->next;
            }
        }
    }
}

void
htable_release(HashTable *t)
{
    for (int i = 0; t->count; i++)
    {
        if (t->table[i])
        {
            TableBucket * bucket = t->table[i];
            while (bucket)
            {
                TableBucket * bucketToFree = bucket;
                entry_free(bucket->entry);
                bucket = bucket->next;
                free(bucketToFree);
                t->count--;
            }
        }
    }
    free(t->table);
}

void
_htable_release(void *t)
{
    htable_release(t);
}





Entry *
entry_create(char *key, void *obj)
{
    Entry * e = (Entry *)malloc(sizeof(Entry));
    e->key = malloc(sizeof(char) * (strlen(key) + 1));
    strcpy(e->key, key);
    e->obj = obj;
    retain(obj);
    return e;
}

void entry_free(Entry *e)
{
    release(e->obj);
    free(e->key);
    free(e);
}

Hash
string_hash(const char * string)
{
    unsigned i = 0;
    unsigned long x = string[i] << 7;
    while (string[i])
        x = (1000003 * x) ^ string[i++];
    x ^= i;
    return x;
}

