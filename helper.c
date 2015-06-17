
#include "helper.h"

#include <assert.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

FILE* try_fopen(const char* path, const char* mode) {
    FILE* fp = fopen(path, mode);
    if (fp == NULL) {
        fprintf(stderr, "unable to open `%s`: %s\n", path, strerror(errno));
    }
    return fp;
}

void* chmalloc(size_t nbytes) {
    void* p = malloc(nbytes);
    assert(p != NULL);
    return p;
}

void eprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

void dbprintf(const char* fmt, ...) {
    va_list args;
    fprintf(stdout, "debug: ");
    va_start(args, fmt);
    vfprintf(stdout, fmt, args);
    va_end(args);
    fprintf(stdout, "\n");
}

BOOL startswith(const char* s1, const char* s2) {
    return s1 && s2 && strncmp(s1, s2, strlen(s2)) == 0;
}

int strtoi(const char* buff) {
    return (int)strtol(buff, NULL, 10);
}

char* dupstr(const char* str) {
    char* newstr = chmalloc(strlen(str) + 1);
    strcpy(newstr, str);
    return newstr;
}

char* strnulchr(char* str, int n) {
    char* result = strchr(str, n);
    if (result == NULL) {
        return str + strlen(str);
    } else {
        return result;
    }
}

