
#include "helper.h"

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
    VIS_ASSERT(p != NULL);
    memset(p, 0, nbytes);
    return p;
}

void* dbmalloc(size_t nbytes, const char* label) {
    void* ptr = chmalloc(nbytes);
    DBPRINTF("Allocated %d bytes for %s: %p", nbytes, label, ptr);
    return ptr;
}

void dbfree(void* ptr, const char* label) {
    DBPRINTF("Freeing %p for %s", ptr, label);
    free(ptr);
}

void eprintf(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
}

static void do_assert_fail(const char* message, const char* file, int line)
    NORETURN;

static void do_assert_fail(const char* message, const char* file, int line) {
    eprintf("Assertion failure: %s:%d: %s", file, line, message);
    abort();
}

void do_assert(BOOL cond, const char* message, const char* file, int line) {
    if (!cond) {
        do_assert_fail(message, file, line);
    }
#if DEBUG > DEBUG_DEBUG
    else {
        DBPRINTF("Assert passes: %s:%d: %s", file, line, message);
    }
#endif
}

void dbprintf(const char* fmt, ...) {
    va_list args;
#if DEBUG > DEBUG_NONE
    fprintf(stderr, "debug: ");
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n");
#else
    (void)fmt;
#endif
}

BOOL fexists(const char* path) {
    int olderrno = errno;
    BOOL exists = FALSE;
    errno = 0;
    FILE* fp = fopen(path, "r+");
    if (fp) {
        exists = TRUE;
        fclose(fp);
    } else if (errno != ENOENT) {
        exists = TRUE;
    }
    errno = olderrno;
    return exists;
}

BOOL startswith(const char* s1, const char* s2) {
    return s1 && s2 && strncmp(s1, s2, strlen(s2)) == 0;
}

int strtoi(const char* buff) {
    return (int)strtol(buff, NULL, 10);
}

char* dupstr(const char* str) {
    char* newstr = DBMALLOC(strlen(str) + 1);
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

static size_t escape_count_copy(char* dest, const char* src) {
    size_t len = 1; /* for trailing \0 */
    size_t i, j;
    for (i = 0, j = 0; src[i] != '\0'; ++i) {
        if (src[i] >= ' ' && src[i] <= '~') {
            if (dest) dest[j++] = src[i];
            ++len;
        } else {
            if (dest) dest[j++] = '\\';
            switch (src[i]) {
                case '\r':
                    if (dest) dest[j++] = 'r';
                    len += 2;
                    break;
                case '\n':
                    if (dest) dest[j++] = 'n';
                    len += 2;
                    break;
                case '\v':
                    if (dest) dest[j++] = 'v';
                    len += 2;
                    break;
                case '\f':
                    if (dest) dest[j++] = 'f';
                    len += 2;
                    break;
                case '\t':
                    if (dest) dest[j++] = 't';
                    len += 2;
                    break;
            default:
                    dest[j++] = 'x';
                    dest[j++] = (char)((src[i] / 10) % 10 + '0');
                    dest[j++] = (char)(src[i] % 10 + '0');
                    len += 4; /* \xNN */
                    break;
            }
        }
    }
    if (dest) {
        dest[len-1] = '\0';
    }
    return len;
}

char* escape_string(const char* str) {
    size_t len;
    char* result = NULL;
    len = escape_count_copy(NULL, str);
    result = DBMALLOC(len);
    VIS_ASSERT(len == escape_count_copy(result, str));
    return result;
}

