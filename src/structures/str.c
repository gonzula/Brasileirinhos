#include <string.h>
#include <stdlib.h>

#include <stdio.h>

#include "str.h"
#include "refcnt.h"


#define BUFFER_SIZE (1 << 8)

void str_free(void *obj);

String * str_init()
{
    String *str = alloc(sizeof(String), str_free);
    str->string = malloc(sizeof(char) * BUFFER_SIZE);
    str->string[0] = 0;
    str->bufferSize = BUFFER_SIZE;
    str->len = 0;
    return str;
}


String * str_create(const char * original)
{
    String *str = alloc(sizeof(String), str_free);
    str->len = strlen(original);
    str->bufferSize = ((str->len + 1)/BUFFER_SIZE + 1) * BUFFER_SIZE;
    str->string = malloc(sizeof(char) * str->bufferSize);
    memcpy(str->string, original, sizeof(char) * (str->len + 1));
    return str;
}

String * str_escape_cstring(char * string)
{
    String *esc = str_init();
    for (int i = 0; string[i]; i++)
    {
        char c = string[i];
        if (c <= '~')
        {
            switch (c)
            {
                case '\"':
                    str_append(esc, "\\\"");
                    break;
                case '\n':
                    str_append(esc, "\\n");
                    break;
                case '\r':
                    str_append(esc, "\\r");
                    break;
                case '\t':
                    str_append(esc, "\\t");
                    break;
                case '\b':
                    str_append(esc, "\\b");
                    break;
                case '\f':
                    str_append(esc, "\\f");
                    break;
                case '\\':
                    str_append(esc, "\\\\");
                    break;
               case '/':
                    str_append(esc, "\\/");
                    break;
                default:
                    str_append_char(esc, c);
                    break;
            }
        }
    }
    return esc;
}

String * str_escape(String *str)
{
    return str_escape_cstring(str->string);
}


void str_append(String *str, const char * toAppend)
{
    size_t appLen = strlen(toAppend);
    if (str->len + appLen + 1 > str->bufferSize)
    {
        str->bufferSize = ((str->len + appLen + 1)/ BUFFER_SIZE + 1) * BUFFER_SIZE;
        str->string = realloc(str->string, sizeof(char) * str->bufferSize);
    }
//    strcat(str->string, toAppend); // menos eficiente
    memcpy(str->string+str->len, toAppend, (appLen + 1) * sizeof(char));
    str->len += appLen;
}

void str_append_char(String *str, const char c)
{
    size_t appLen = 1;
    if (str->len + appLen + 1 > str->bufferSize)
    {
        str->bufferSize = ((str->len + appLen + 1)/ BUFFER_SIZE + 1) * BUFFER_SIZE;
        str->string = realloc(str->string, sizeof(char) * str->bufferSize);
    }
    *(str->string+str->len) = c;
    *(str->string+str->len+1) = 0;
    str->len += appLen;
}

void str_free(void *obj)
{
    String *str = (String *) obj;
    free(str->string);
}
