#ifndef __serializable_H_
#define __serializable_H_

#include "structures.h"

typedef enum
{
    ht_t,
    list_t,
    str_t,
    int_t,
    float_t,
    bool_t,
    null_t
} SerializableType;

typedef struct {
    union
    {
        HashTable *ht;
        List *list;
        String *str;
        int i;
        float f;
        void *obj;
    };
    SerializableType type;
} Serializable;

Serializable * serializable_init();
Serializable * serializable_create(void *obj, SerializableType type);
String * serializable_write_json(Serializable *s);
Serializable * serializable_read_json(String *str);

#endif //__serializable_H_
