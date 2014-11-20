#include <stdio.h>
#include <string.h>


#include "serializable.h"
#include "refcnt.h"

#define isblank(c) (strchr(" \n\r", c) != NULL)
#define isprimitive(c) (strchr("-0123456789eEfalsetruenull.", c) != NULL)
#define streq(a, b) (strcmp(a,b)==0)

void serializable_free(void *sobj);

Serializable *
serializable_init()
{
    Serializable *s = (Serializable *)alloc(sizeof(Serializable), serializable_free);
    s->obj = NULL;
    s->type = 0;
    return s;
}

Serializable *
serializable_create(void *obj, SerializableType type)
{
    Serializable *s = (Serializable *)alloc(sizeof(Serializable), serializable_free);
    retain(obj);
    switch (type)
    {
        case ht_t:
        case list_t:
        case str_t:
            s->obj = obj;
            break;
        default:
            break;
    }
    s->type = type;
    return s;
}

void
_serialize_ht(Entry *entry, int i, int count, int *stop, void *context)
{
    char *key = entry->key;
    Serializable *s = (Serializable *)entry->obj;
    String *str = (String *)context;
    str_append(str, "\"");
    String *escaped = str_escape_cstring(key);
    str_append(str, escaped->string);
    release(escaped);
    str_append(str, "\":");
    String *sout = serializable_write_json(s);
    str_append(str, sout->string);
    if (i < count - 1)
        str_append_char(str, ',');
    release(sout);
}

String *
serializable_write_json(Serializable *s)
{
    String *str = str_init();
    switch (s->type)
    {
        case str_t:
            str_append(str, "\"");
            String *escaped = str_escape(s->str);
            str_append(str, escaped->string);
            release(escaped);
            str_append(str, "\"");
            break;
        case list_t:
            str_append(str, "[");
            LIST_LOOP(s->list)
            {
                String *nodeStr = serializable_write_json(node->object);
                str_append(str, nodeStr->string);
                if (node->next)
                    str_append(str, ",");
                release(nodeStr);
            }
            str_append(str, "]");
            break;
        case ht_t:
            str_append(str, "{");
            htable_iterate(s->ht, str, _serialize_ht);
            str_append(str, "}");
            break;
        case int_t:
        {
            char num[20];
            sprintf(num, "%d", s->i);
            str_append(str, num);
            break;
        }
        case float_t:
        {
            char num[100];
            sprintf(num, "%f", s->f);
            str_append(str, num);
            break;
        }
        case bool_t:
            str_append(str, s->i?"true":"false");
            break;
        case null_t:
            str_append(str, "null");
            break;

        default:
            break;
    }
    return str;
}

Serializable * _read_json           (char *str, size_t len, int *outPos);
Serializable * _read_json_list      (char *str, size_t len, int *outPos);
Serializable * _read_json_string    (char *str, size_t len, int *outPos);
Serializable * _read_json_ht        (char *str, size_t len, int *outPos);
Serializable * _read_json_primitive (char *str, size_t len, int *outPos);

Serializable *
serializable_read_json(String *str)
{
    int op;
    return _read_json(str->string, str->len, &op);
}


Serializable *
_read_json(char *str, size_t len, int *outPos)
{
    int i;
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        if (isblank(c))continue;
        if (c == '[')
        {
            return _read_json_list(&str[i+1], len-i-1, outPos);
        }
        if (c == '{')
        {
            return _read_json_ht(&str[i+1], len-i-1, outPos);
        }
        if (c == '\"')
        {
            return _read_json_string(&str[i+1], len-i-1, outPos);
        }
        if (isprimitive(c))
        {
            return _read_json_primitive(&str[i], len-i, outPos);
        }
        return NULL;
    }
    return NULL;
}

Serializable *
_read_json_primitive (char *str, size_t len, int *outPos)
{
    String *s = str_init();
    int i;
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        if (!isprimitive(c))break;
        str_append_char(s, c);
    }
    Serializable *ser = serializable_init();
    if (streq(s->string, "null"))
        ser->type = null_t;
    else if (streq(s->string, "true"))
    {
        ser->type = bool_t;
        ser->i = 1;
    }
    else if (streq(s->string, "false"))
    {
        ser->type = bool_t;
        ser->i = 0;
    }
    else if (strchr(s->string, '.') || strchr(s->string, 'e') || strchr(s->string, 'E'))//float
    {
        ser->type = float_t;
        sscanf(s->string, "%f", &ser->f);
    }
    else
    {
        ser->type = int_t;
        sscanf(s->string, "%d", &ser->i);
    }

    release(s);
    *outPos = i-1;
    return ser;
}

Serializable *
_read_json_string(char *str, size_t len, int *outPos)
{
    String *s = str_init();
    int i;
    int isEscaped = 0;
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        if (c == '\"' && !isEscaped)
            break;
        str_append_char(s, c);
    }
    *outPos = i+1;
    Serializable *ser = serializable_create(s, str_t);
    release(s);
    return ser;
}

Serializable *
_read_json_list(char *str, size_t len, int *outPos)
{
    List *list = list_init();
    int i;
    int state = 0;
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        if (isblank(c))continue;
        if (state == 0)
        {
            int op;
            Serializable *s = _read_json(str + i, len - i, &op);
            list_append(list, s);
            release(s);
            i += op;
            state = 1;
            continue;
        }
        if (state == 1)
        {
            if (c == ',')
            {
                state = 0;
                continue;
            }
            if (c == ']')
            {
                break;
            }
        }
    }
    Serializable *s = serializable_create(list, list_t);
    release(list);
    *outPos = i+1;
    return s;
}

Serializable *
_read_json_ht(char *str, size_t len, int *outPos)
{
    HashTable *t = htable_init();
    int i;
    int state = 0;              // 0 - waiting key
                                // 1 - waiting colon
                                // 2 - waiting value
                                // 3 - waiting comma
    Serializable *keyHolder;
    for (i = 0; i < len; i++)
    {
        char c = str[i];
        if (isblank(c))continue;
        if (state == 0)
        {
            if (c == '\"')
            {
                int op;
                keyHolder = _read_json_string(str+i+1, len-i-1, &op);
                i += op;
                state = 1;
                continue;
            }
            else
                break;
        }
        if (state == 1)
        {
            if (c == ':')
                state = 2;
            continue;
        }
        if (state == 2)
        {
            int op;
            Serializable *s = _read_json(str+i, len-i, &op);
            htable_set(t, keyHolder->str->string, s);
            release(keyHolder);
            release(s);
            i += op;
            state = 3;
            continue;
        }
        if (state == 3)
        {
            if (c == ',')
            {
                state = 0;
                continue;
            }
            if (c == '}')
            {
                break;
            }
        }
    }
    Serializable *s = serializable_create(t, ht_t);
    release(t);
    *outPos = i+1;
    return s;
}

void
serializable_free(void *sobj)
{
    Serializable *s = (Serializable *)sobj;
    switch (s->type)
    {
        case ht_t:
        case list_t:
        case str_t:
            release(s->obj);
            break;
        default:
            break;
    }
}
