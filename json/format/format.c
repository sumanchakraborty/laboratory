
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "format.h"

#define EMIT(x) do { if (j < rem_len) off[j++] = x; } while (0)

int ixjson_format_int(char *buf, char *off, long int value) {
    int rem_len = &buf[MAX_LENGTH] - off;
    return rem_len <= 0 ? 0 : snprintf(off, rem_len, "%ld", value);
}

int ixjson_format_double(char *buf, char *off, double value) {
    int rem_len = &buf[MAX_LENGTH] - off;
    return rem_len <= 0 ? 0 : snprintf(off, rem_len, "%g", value);
}

int ixjson_format_quoted_str(char *buf, char *off, const char *str) {
    int i = 0, j = 0, ch;
    int rem_len = &buf[MAX_LENGTH] - off;

    EMIT('"');
    while ((ch = str[i++]) != '\0' && j < rem_len) {
        switch (ch) {
            case '"':  EMIT('\\'); EMIT('"'); break;
            case '\\': EMIT('\\'); EMIT('\\'); break;
            case '\b': EMIT('\\'); EMIT('b'); break;
            case '\f': EMIT('\\'); EMIT('f'); break;
            case '\n': EMIT('\\'); EMIT('n'); break;
            case '\r': EMIT('\\'); EMIT('r'); break;
            case '\t': EMIT('\\'); EMIT('t'); break;
            default: EMIT(ch);
        }
    }
    EMIT('"');
    EMIT(0);

    return j == 0 ? 0 : j - 1;
}

int ixjson_format_raw_str(char *buf, char *off, const char *str) {
    int rem_len = &buf[MAX_LENGTH] - off;
    return rem_len <= 0 ? 0 : snprintf(off, rem_len, "%s", str);
}

